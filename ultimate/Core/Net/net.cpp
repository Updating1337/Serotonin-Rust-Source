#include "net.h"
#include "steam_session.h"
#include "offsets.h"

#ifdef SUPPORTS_COMPRESSION
	#include "miniz.h"
#endif

#ifdef WEB_RADAR_FEATURE
	#include "../features/WebRadar.h"
#endif

#ifdef CONFIG_FEATURE
	#include "ConfigManager.h"
#endif

#ifdef HAS_CRT
	#include <chrono>
	std::shared_ptr<Net> net = nullptr;
#else
	Net* net = nullptr;
#endif

Net::Net(uintptr_t steam_api) : exit_flag_(false), ready_(false), web_radar_started_(false), steam_networking(nullptr)
{
	steam_networking = ((ISteamClient * (__cdecl*)())steam_api)();

#ifdef HAS_CRT
	networking_steam = std::make_shared<connector::steam_session>(IP, PORT, TOKEN);
	UnstopabbleThread(worker);
#else
	//IF HAS_CRT is not defined you have to set your IP as uint32_t http://www.aboutmyip.com/AboutMyXApp/IP2Integer.jsp 
	//The intiger converted value goes into the 1st parameter
	networking_steam = new connector::steam_session(steam_networking, 92771667, PORT, std::string((const char*)TOKEN));
#endif
}

Net::~Net() {
#ifndef HAS_CRT
	free(networking_steam);
#endif
}

#ifndef HAS_CRT
bool Net::run()
{
	if (!steam_networking) {
		SteamConnectorError = true;
		return false;
	}

	//check if we want to run our networking
	if (exit_flag_.load()) {
		SteamConnectorError = true;
		return false;
	}

	//check if networking is ready
	if (!networking_steam) {
		SteamConnectorError = true;
		return false;
	}

	//check if we're connected
	if (!networking_steam->isConnected()) {
		SteamConnectorError = true;
		return false;
	}

	//lets send token if we haven't already
	networking_steam->sendToken();

	//if we were not ready, lets signal that we're ready!
	if (!net->ready_.load()) {
		net->ready_.store(true);
	}

	auto out = networking_steam->process();
	net->proceed_inc_data(out);
	keep_alive();

	if (networking_steam->failed.load())
	{
		SteamConnectorError = true;
		return false;
	}
	return true;
}
#endif

void Net::send_data(connector::data& data)
{
	networking_steam->send_data(data);
}

void Net::send_data(std::vector<connector::data>& data)
{
	for (auto& iter : data) {
		send_data(iter);
	}
}

void Net::keep_alive() {
	connector::cheat_message msg;
	msg.msg = connector::messages::NONE;
	msg.value = "...";
	connector::data packet = connector::data(msg);
	networking_steam->send_data(packet, 0);
}

#ifdef HAS_CRT
void Net::worker() {
	//wait for networking to be ready
	while (!networking_steam) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

		if (net->exit_flag_.load())
			return;
	}

	//wait for the client to connect
	while (true) {
		if (networking_steam->isConnected())
			break;

		if (net->exit_flag_.load())
			return;
	}
	LOG("[DEBUG] Net - Connected");
	//send token
	networking_steam->sendToken();
	net->ready_.store(true);	

	LOG("[DEBUG] Net - Ready");
	net->requestAllFonts();

	//ready
	while (!net->exit_flag_.load()) {
		auto out = networking_steam->process();
		net->proceed_inc_data(out);
		
		//keep alive
		connector::cheat_message msg;
		msg.msg = connector::messages::NONE;
		msg.value = "...";
		networking_steam->send_data(connector::data(msg));

		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}
#endif

void Net::request_offset(uint32_t hash, uint32_t base_index) {
	connector::offsets offset;
	offset.hash = hash;
	offset.base_index = base_index;
	offset.game = CURRENT_GAME;
	networking_steam->send_data(connector::data(offset));
}

#ifdef SUPPORTS_COMPRESSION
std::vector<unsigned char> decompres_data(std::vector<unsigned char> data) {
	uLong src_len = data.size();
	uLong cmp_len = compressBound(src_len);
	uLong uncomp_len = 10000000000;

	std::vector<unsigned char> pCmp;
	pCmp.resize(uncomp_len);

	// Compress the string.
	auto cmp_status = uncompress(pCmp.data(), &uncomp_len, (const unsigned char*)data.data(), src_len);
	if (cmp_status != Z_OK)
	{
		return {};
	}
	pCmp.resize(uncomp_len);

	return pCmp;
}
#endif

void Net::process_inc_messages(connector::cheat_message& msg) {
#ifdef CONFIG_FEATURE
	connector::cloud_config cfg;
#endif

	switch (msg.msg) {
#ifdef WEB_RADAR_FEATURE
	case connector::messages::REQUEST_WEB_RADAR_CODE:
		WebRadar::get().set_share_code(msg.value, msg.value_int);
		break;
#endif

#ifdef CONFIG_FEATURE
	case connector::messages::GET_MY_NAME:
		Config::Get().set_user_id(msg.value);
		Config::Get().refresh_list();
		break;
	case connector::messages::CFG_SUCCESSFUL:
		LOG(XS("[DEBUG] CFG SUCESS!!"));
		break;	
	case connector::messages::CFG_FAILED:
		LOG(XS("[DEBUG] CFG FAILED: %s %u"), msg.value.c_str(), msg.value_int);
		break;
#endif

	case connector::messages::ERROR_RESPONSE:
		LOG(XS("[DEBUG] File upload error %s\n"), msg.value.c_str());
		break;

	default:
		break;
	}
}

struct Vec3
{
	float x;
	float y;
	float z;
};

void Net::proceed_inc_data(std::vector<connector::data>& data)
{
	for (auto& iter : data) {
		auto type = iter.get_type();
		if (type == connector::data::type::MESSAGE) {
			connector::cheat_message msg = std::get<connector::cheat_message>(iter.get_data());
			process_inc_messages(msg);
		}
		else if (type == connector::data::type::OFFSETS) {
			connector::offsets offset = std::get<connector::offsets>(iter.get_data());
			OffsetManager::Get().add_offset(offset);
		}
		else if (type == connector::data::type::FILE) {
			FileHandle file;
			auto iter_data = std::get<connector::file>(iter.get_data());
			if (iter_data.compressed) {
#ifdef SUPPORTS_COMPRESSION
				file.data = decompres_data(iter_data.data);
				file.size = file.data.size();
				shared_files_.push_back(file);
#else
				LOG("[DEBUG] Error unsupported, recieved compressed FILE message!");
				continue;
#endif
			}
			else {
				file.data = iter_data.data;
				file.size = iter_data.size;
			}
			file.name = iter_data.name;
			LOG(XS("[DEBUG] Got File %s"), file.name.c_str());

#ifdef HAS_CRT
			std::lock_guard<std::mutex> lock(net->shared_files_mutex_);
#else
			net->shared_files_mutex_.lock();
#endif
			net->shared_files_.push_back(file);
#ifndef HAS_CRT
			net->shared_files_mutex_.unlock();
#endif
		}
		else if (type == connector::data::type::SLICED_DATA)
		{
			//we've got sliced data from server, so we need to rebuild the original big message
			process_sliced_message(iter);
		}
#ifdef CONFIG_FEATURE
		else if (type == connector::data::type::CLOUD_CONFIG) {
			process_config_data(iter);
		}
#endif
		else if (type == connector::data::type::SHARED_ESP) {
			auto iter_data = std::get<connector::shared_esp_data>(iter.get_data());
			//std::string username;

			//connector::reader reader(iter_data.data.data(), iter_data.data.size());
			//username = reader.read<std::string>();

			//xCheatsKey = (const char*)username.c_str();

			//auto wideKey = (const char*)username.c_str();
			//if (std::find(xCheatsArr.begin(), xCheatsArr.end(), wideKey) == xCheatsArr.end()) {
			//	xCheatsArr.push_back(wideKey);
			//}
			std::string Message;
			connector::reader reader(iter_data.data.data(), iter_data.data.size());
			Message = reader.read<std::string>();

			GlobalMessage = (const char*)Message.c_str();

			LOG(XS("[DEBUG] Message: %s"), (const char*)Message.c_str());





			//LOG("[DEBUG] [SharedESP #%zu] SteamID = %s\n", iter_data.channel, username.c_str());
			// 
			// 
			//LOG("[DEBUG] [SharedESP #%zu] LocalPos.x = %f\n", iter_data.channel, SharedLocalPos.x);
			//LOG("[DEBUG] [SharedESP #%zu] LocalPos.y = %f\n", iter_data.channel, SharedLocalPos.y);
			//LOG("[DEBUG] [SharedESP #%zu] LocalPos.z = %f\n", iter_data.channel, SharedLocalPos.z);

			//if (!LocalBoxBounds.empty())
			//{
			//	LOG("[DEBUG] [SharedESP #%zu] BoxBounds.left = %f\n", iter_data.channel, LocalBoxBounds.left);
			//	LOG("[DEBUG] [SharedESP #%zu] BoxBounds.right = %f\n", iter_data.channel, LocalBoxBounds.right);
			//	LOG("[DEBUG] [SharedESP #%zu] BoxBounds.top = %f\n", iter_data.channel, LocalBoxBounds.top);
			//	LOG("[DEBUG] [SharedESP #%zu] BoxBounds.bottom = %f\n", iter_data.channel, LocalBoxBounds.bottom);
			//}
			//LOG(XS("[DEBUG] [SharedESP #%zu] %s\n"), iter_data.channel, username.c_str());
			 
			//xCheatsUserArr.push_back((const char*)iter_data.data.data());

			//xCheatsUserArr = iter_data.data.data();

			//	auto iter_data = std::get<connector::shared_esp_data>(iter.get_data());
			//	/*uint32_t x;
			//	uint32_t y;
			//	uint32_t z;*/
			//	std::string username;

			//	connector::reader reader(iter_data.data.data(), iter_data.data.size());
			///*	x = reader.read<uint32_t>();
			//	y = reader.read<uint32_t>();
			//	z = reader.read<uint32_t>();*/
			//	username = reader.read<std::string>();

			//	LOG(XS("[DEBUG] [SharedESP #%zu] %s\n"), iter_data.channel, username.c_str());




			/* Multi Receive Example */
			//auto iter_data = std::get<connector::shared_esp_data>(iter.get_data());
			//std::string username;
			//uint64_t steamID;

			//connector::reader reader(iter_data.data.data(), iter_data.data.size());
			//username = reader.read<std::string>();
			//steamID = reader.read<uint64_t>();

			////printf("[SharedESP #%zu] %s\n", iter_data.channel, (const char*)iter_data.data.data());

			//printf("[DEBUG] [SharedESP #%zu] %s %zu\n", iter_data.channel, username.c_str(), steamID);
		}
	}
}

bool Net::rebuildMessageFromSlices(build_slices& data, std::vector<unsigned char>& out_data) {
	if (data.max_slices != data.slices.size())
		return false;
	
	uint16_t slices_read = 0;
	out_data.clear();
	//at this point we need to put all slices togather
	while (slices_read < data.max_slices) {
		for (connector::sliced_data& iter : data.slices) {
			if (iter.slice_index != slices_read)
				continue;

			//append data from slice
			out_data.insert(out_data.end(), iter.data.begin(), iter.data.end());
			// move to next slice
			slices_read++;
			break;
		}
	}
	if (slices_read >= data.max_slices)
		return true;

	return false;
}

void Net::requestAllFonts()
{
	connector::cheat_message msg_get_font;
#ifdef SUPPORTS_COMPRESSION
	msg_get_font.value = "zip"; //compress files!
#endif
	msg_get_font.msg = connector::messages::GET_FONT_FA_SOLID;

	networking_steam->send_data(connector::data(msg_get_font));

	msg_get_font.msg = connector::messages::GET_FONT_NOTOSANS_REGULAR;
	networking_steam->send_data(connector::data(msg_get_font));

	msg_get_font.msg = connector::messages::GET_FONT_NOTOSANS_BOLD;
	networking_steam->send_data(connector::data(msg_get_font));
}

#ifdef CONFIG_FEATURE
void Net::process_config_data(connector::data& data)
{
	if (data.get_type() != connector::data::type::CLOUD_CONFIG)
		return;

	auto iter_data = std::get<connector::cloud_config>(data.get_data());
	
	switch (iter_data.action) {
	case connector::cloud_action::CLOUD_GET:
		Config::Get().load_config_data(iter_data.data);
		break;
	case connector::cloud_action::CLOUD_GET_LIST_FROM_USER:
		//ToDo: option to browse others configs in cheat
	case connector::cloud_action::CLOUD_GET_LIST_FROM_CURR_USER:
		Config::Get().add_config_info(iter_data.config_id, iter_data.config_name, iter_data.user_id, iter_data.is_public);
		break;
	case connector::cloud_action::CLOUD_CHANGE_PUBLIC_STATUS:
		Config::Get().update_public_status(iter_data.config_id, iter_data.is_public);
		break;
	//those are only ment for sending to server, not the other way around
	case connector::cloud_action::CLOUD_REMOVE:
	case connector::cloud_action::CLOUD_RENAME:
	case connector::cloud_action::CLOUD_UPLOAD:
	case connector::cloud_action::CLOUD_NONE:
	default:
		break;
	}

	Config::Get().update_list_from_net();
}
void Net::send_config_data(connector::cloud_config& data)
{
	networking_steam->send_data(connector::data(data));
}
#endif

bool Net::process_sliced_message(connector::data& data)
{
	std::vector<unsigned char> big_message;
	bool found_slice = false;
	bool found_data = false;
	auto iter_data = std::get<connector::sliced_data>(data.get_data());

	//lets find if we have any slices already, if we do add this to them
	for (auto& slice : slices_builder) {
		if (slice.packet_id != iter_data.packet_id) {
			continue;
		}

		//we have some slices of this message already
		found_data = true;

		//check if we already got same slice of this message
		for (auto& slice_indexes : slice.slices) {
			if (slice_indexes.slice_index != iter_data.slice_index)
				continue;

			found_slice = true;
			break;
		}

		//if we have this slice of this message let's skip this
		if (found_slice)
			break;

		//if we got here, that means we have builder for this message
		// but this slice is missing, lets add it to out builder then
		slice.slices.push_back(iter_data);

		//check if we have all slices of the message, if we do let's re-create the message
		if (rebuildMessageFromSlices(slice, big_message)) {
			//we've got the full message! lets read it
			auto messages = networking_steam->read_data(big_message);
			// since we have read the message we can process all data in it
			proceed_inc_data(messages);
			return true;
		}

		break;
	}

	//if we found slice in our message builder, 
	// that means we have everything we needed for this moment so continue
	if (found_data)
		return false;

	//make new record for this message and add current slice to it
	build_slices new_build_slice;
	new_build_slice.max_slices = iter_data.max_slices;
	new_build_slice.packet_id = iter_data.packet_id;
	new_build_slice.slices.push_back(iter_data);
	slices_builder.push_back(new_build_slice);
	return false;
}

