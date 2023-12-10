#pragma once
#include "config.h"
#include <atomic>
#include <memory>
#include "file_share.h"

#ifdef HAS_CRT
	#include <mutex>
#else
	#include "../CRT/mutex/smutex.hpp"
#endif

namespace connector {
	class data;
	struct sliced_data;
	struct web_radar_info;
	struct cheat_message;
	struct cloud_config;
}

class ISteamClient;

class Net {
public:
	Net(uintptr_t steam_api);
	~Net();

	bool run();
	void keep_alive();
	void send_data(connector::data& data);
	void send_data(std::vector<connector::data>& data);
#ifdef HAS_CRT
	static void worker();
#endif
	void request_offset(uint32_t hash, uint32_t base_index);
#ifdef CONFIG_FEATURE
	void send_config_data(connector::cloud_config& data);
#endif
	void process_inc_messages(connector::cheat_message& msg);
	void proceed_inc_data(std::vector<connector::data>& data);
	std::vector<FileHandle> shared_files_;

#ifdef HAS_CRT
	std::mutex shared_files_mutex_;
#else
	rb::smutex shared_files_mutex_;
#endif

	std::atomic_bool ready_;
	std::atomic_bool exit_flag_;
	std::atomic_bool web_radar_started_;
private:
	static void requestAllFonts();
#ifdef CONFIG_FEATURE
	void process_config_data(connector::data& data);
#endif
	bool process_sliced_message(connector::data& data);
	//sliced messages
	struct build_slices {
		uint16_t max_slices;
		uint32_t packet_id;
		std::vector<connector::sliced_data> slices;
	};
	std::vector<build_slices> slices_builder;
	bool rebuildMessageFromSlices(build_slices& data, std::vector<unsigned char>& out_data);

	ISteamClient* steam_networking;
};

#ifdef HAS_CRT
	extern std::shared_ptr<Net> net;
#else
	extern Net* net;
#endif