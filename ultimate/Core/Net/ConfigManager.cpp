#include "ConfigManager.h"
#include "miniz.h"
#include "data.h"
#include "net.h"

static std::vector<unsigned char> compress_data(std::string& data) {
	uLong src_len = data.size();
	uLong cmp_len = compressBound(src_len);
	uLong uncomp_len = src_len;

	std::vector<unsigned char> pCmp;
	pCmp.resize(src_len);

	auto cmp_status = compress(pCmp.data(), &cmp_len, (const unsigned char*)data.data(), src_len);
	if (cmp_status != Z_OK)
	{
		return {};
	}
	pCmp.resize(cmp_len);

	return pCmp;
}

static std::string decompress_data(const std::vector<unsigned char>& data) {
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

	return std::string(pCmp.begin(), pCmp.end());
}

Config::Config()
{
}

void Config::load_config_data(const std::vector<unsigned char>& data)
{
	//This implementation is completley up to you, we have used json formating, but feel free to use anything
#if 0
	auto cfg_str = decompress_data(data);
	nlohmann::json json = nlohmann::json::parse(cfg_str, nullptr, false);
	if (json.is_discarded()) // prevent crash if config parse failed
		return;

	Form->Load(json);
#endif
}

std::vector<unsigned char> Config::get_config_data()
{
	//This implementation is completley up to you, we have used json formating, but feel free to use anything
#if 0
	nlohmann::json json;
	json.clear();
	Form->Save(json);

	auto cfg_str = json.dump();
	auto file = compress_data(cfg_str);

	return file;
#endif
	return {};
}

void Config::save_config()
{
	connector::cloud_config cfg_req;
	cfg_req.data = get_config_data();
	cfg_req.action = connector::cloud_action::CLOUD_UPLOAD;
	list_lock.lock();
	if (selected_config < list.size())
	{
		auto cfg_info = list[selected_config];
		cfg_req.config_name = cfg_info.name;
		cfg_req.config_id = cfg_info.id;
	}
	else {
		cfg_req.config_name = XS("DEFAULT");
		cfg_req.config_id = 0;
		cfg_req.is_public = false;
	}
	list_lock.unlock();
	net->send_config_data(cfg_req);
}

void Config::save_new_config(std::string name, bool is_public)
{
	if (name.length() < 3)
		return;

	connector::cloud_config cfg_req;
	cfg_req.action = connector::cloud_action::CLOUD_UPLOAD;
	cfg_req.config_name = name;
	cfg_req.data = get_config_data();
	cfg_req.is_public = is_public;
	cfg_req.user_id = my_user_id;
	cfg_req.config_id = 0;
	net->send_config_data(cfg_req);
}

void Config::remove_config()
{
	list_lock.lock();
	if (selected_config < list.size())
	{
		auto cfg_info = list[selected_config];
		connector::cloud_config cfg_req;
		cfg_req.action = connector::cloud_action::CLOUD_REMOVE;
		cfg_req.config_id = cfg_info.id;
		net->send_config_data(cfg_req);
	}
	clear_list(false);
	list_lock.unlock();
}

void Config::change_public_status(bool new_state, bool is_locked)
{
	if (!is_locked)
		list_lock.lock();

	if (selected_config < list.size())
	{
		auto cfg_info = list[selected_config];
		connector::cloud_config cfg_req;
		cfg_req.action = connector::cloud_action::CLOUD_CHANGE_PUBLIC_STATUS;
		cfg_req.config_id = cfg_info.id;
		cfg_req.is_public = new_state;
		net->send_config_data(cfg_req);
	}

	if (!is_locked)
		list_lock.unlock();
}

void Config::refresh_list()
{
	clear_list();
	
	connector::cloud_config cfg_req;
	cfg_req.action = connector::cloud_action::CLOUD_GET_LIST_FROM_CURR_USER;
	cfg_req.user_id = my_user_id;

	net->send_config_data(cfg_req);
}

void Config::request_selected_config()
{
	list_lock.lock();
	if (selected_config < list.size())
	{
		auto cfg_info = list[selected_config];
		connector::cloud_config cfg_req;
		cfg_req.action = connector::cloud_action::CLOUD_GET;
		cfg_req.config_id = cfg_info.id;
		net->send_config_data(cfg_req);
	}
	list_lock.unlock();
}
