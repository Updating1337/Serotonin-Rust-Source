#pragma once
#include "config.h"
#include <cstdint>
#include <string>
#include <variant>

#include "reader.h"
#include "writer.h"

namespace connector {

	enum messages {
		NONE,
		SET_PUB_KEY = 19,				//Server->Client only TCP!
		DROPPED = 26,					//Server->Client only
		REQUEST_SCREENSHOT = 2,			//Server->Client only
		EXECUTE = 15, 					//Server->Client only
		STAY_ALIVE = 13,				//NONE+
		GET_SERVER_INFO = 14,		    //ServerManager+	
		TOGGLE_DEMO_WEB_RADAR = 10,		//ServerManager+	
		GET_MY_NAME = 7,				//AUTHENTIFICATED+
		CFG_SUCCESSFUL = 4,				//AUTHENTIFICATED+
		CFG_FAILED = 20,				//AUTHENTIFICATED+
		NEW_LOG = 24,					//ServerManager
		SET_MAINTENANCE = 25,			//ServerManager
		GET_MAINTENANCE = 27,			//UN_AUTHENTIFICATED+
		SHUTDOWN_SERVER = 9,			//ServerManager+
		GET_FONT_FA_SOLID = 1,			//AUTHENFICICATED+
		GET_FONT_NOTOSANS_REGULAR = 22, //AUTHENFICICATED+
		GET_FONT_NOTOSANS_BOLD = 8,		//AUTHENFICICATED+
		GET_FILE = 40,					//AUTHENFICICATED+
		BLACK_LIST_ADD = 28,			//ServerManager+
		BLACK_LIST_REMOVE = 29,			//ServerManager+ 
		BLACK_LIST_FETCH = 30,			//ServerManager+ 
		GET_DETAILED_USER_LIST = 31,	//ServerManager+ 
		FORCE_DISCONNECT = 32,			//ServerManager+
		REQUEST_WEB_RADAR_CODE = 33,	//AUTHENFICICATED+
		LOGIN_SUCESS = 34,				//UN_AUTHENFICICATED
		LOGIN_FAILED = 35,				//UN_AUTHENFICICATED
		CHECK_VERSION_CSGO = 36,		//AUTHENFICICATED+
		CHECK_CSGO_EXTERNAL_SHA1 = 37,	//AUTHENFICICATED+
		JOIN_SHARED_ESP = 38,			//SHARED_ESP+
		LEAVE_SHARED_ESP = 39,			//SHARED_ESP+
		ERROR_RESPONSE = 41,			//Server->Client only
		WARNING_RESPONSE = 42,			//Server->Client only
		COUNT_MESSAGES = 43				//INVALID
	};

	struct cheat_message {
		messages msg = messages::NONE;
		std::string value = "";
		uint32_t value_int = 0;
	};

	enum offset_action {
		GET_OFFSET_BY_HASH = 0,
#ifdef SERVER_MANAGER
		GET_OFFSET_BY_NAME = 1, 		//ServerManager only
		SET_OFFSET = 2,  				//ServerManager only
		LOAD_OFFSETS_FROM_FILE = 3,  	//ServerManager only
		SAVE_OFFSETS_TO_FILE = 4,	  	//ServerManager only
		GET_ALL_OFFSETS = 5,			//ServerManager only
		REMOVE_OFFSET = 6,				//ServerManager only
		IMPORT_JSON = 7,				//ServerManager only
		EXPORT_JSON = 8,				//ServerManager only
#endif
		SET_BASE_ADDRESS = 9
	};

	struct offsets {
		offset_action action;
		std::string name;
		uint32_t hash;
		uint32_t base_index;
		uint64_t value;
		uint16_t game;
		offsets() : action(GET_OFFSET_BY_HASH), name(""), hash(0), value(0), game(0), base_index(0) {};
	};

	struct file {
		std::string name;
		std::vector<unsigned char> data;
		uint32_t size;
		uint32_t size_without_compression;
		bool compressed;
	};

	struct sliced_data {
		uint16_t packet_id;
		uint16_t slice_index;
		uint16_t max_slices;
		std::vector<unsigned char> data;
	};
	
	struct invalid {
		bool a;
		bool b;
		invalid() : a(false), b(false) {}
	};

#ifdef CSGO_STRUCTS
	struct player {
		std::string name;
		uint16_t weap_id;
		float x;
		float y;
		float angle;
		std::string steamid;
		uint16_t hp;
		uint16_t team;
	};

	struct nade {
		uint16_t type;
		float x;
		float y;
	};

	struct web_radar_info {
		uint32_t share_code_hash;
		std::string map;
		uint16_t players_size;
		std::vector<player> players;
		float bomb_x;
		float bomb_y;
		uint32_t bomb_time;
		uint16_t nades_size;
		std::vector<nade> nades;
	};
#endif

#ifdef CONFIG_FEATURE
	enum cloud_action {
		CLOUD_NONE, //INVALID
		CLOUD_UPLOAD, //everything is required
		CLOUD_GET_LIST_FROM_CURR_USER, // nothing is required
		CLOUD_GET_LIST_FROM_USER, // user id is required
		CLOUD_GET, //config id is required
		CLOUD_REMOVE, //config id is required
		CLOUD_RENAME, //config id and new config_name is required
		CLOUD_CHANGE_PUBLIC_STATUS // config_id, is_public is required
	};

	struct cloud_config {
		cloud_action action; //required
		uint32_t config_id; //required
		std::string config_name; //required
		std::vector<unsigned char> data;
		bool is_public;
		std::string user_id; //required
	};
#endif

	struct shared_esp_data
	{
		std::vector<unsigned char> data;
		uint32_t channel;
	};

	struct report {
		std::string id;
		std::string extra;
		std::string hwid;
		bool has_file;
		file file_;
	};

	typedef std::variant<offsets, cheat_message, file, invalid, shared_esp_data, report, sliced_data
#ifdef CONFIG_FEATURE
		, cloud_config
#endif
#ifdef CSGO_STRUCTS
		, web_radar_info
#endif
		> data_variant;

	class data {
	public:
		enum class type {
			INVALID, OFFSETS, USER_INFO, USER_LIST, USER_UPDATE, MESSAGE, FILE, SLICED_DATA,
			BLACK_LIST, EX_USER_LIST, WEB_RADAR, CLOUD_CONFIG, CHEAT_LOGIN, QUEUE_MESSAGE, REPORT, SHARED_ESP
		};

		inline data(data_variant data_) : data_struct_(data_) {}

		inline type get_type() const {

			if (std::holds_alternative<offsets>(data_struct_)) {
				return data::type::OFFSETS;
			}

			if (std::holds_alternative<cheat_message>(data_struct_)) {
				return data::type::MESSAGE;
			}

			if (std::holds_alternative<file>(data_struct_)) {
				return data::type::FILE;
			}

			if (std::holds_alternative<invalid>(data_struct_)) {
				return data::type::INVALID;
			}

			if (std::holds_alternative<shared_esp_data>(data_struct_)) {
				return data::type::SHARED_ESP;
			}

			if (std::holds_alternative<report>(data_struct_)) {
				return data::type::REPORT;
			}
#ifdef CONFIG_FEATURE			
			if (std::holds_alternative<cloud_config>(data_struct_)) {
				return data::type::CLOUD_CONFIG;
			}
#endif
#ifdef CSGO_STRUCTS
			if (std::holds_alternative<web_radar_info>(data_struct_)) {
				return data::type::WEB_RADAR;
			}
#endif

			if (std::holds_alternative<sliced_data>(data_struct_)) {
				return data::type::SLICED_DATA;
			}

			return data::type::INVALID;
		}

		inline data_variant get_data() const {
			return data_struct_;
		}

	private:
		friend class write_traits<data>;

		data_variant data_struct_;
	};

	template<>
	class read_traits<data> {
	public:
		static data read(reader& reader);
	};

	template<>
	class write_traits<data> {
	public:
		static void write(writer& writer, const data& client);
	};

}