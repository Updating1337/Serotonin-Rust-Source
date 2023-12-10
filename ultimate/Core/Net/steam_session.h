#pragma once
#include "config.h"
#ifdef ALLOW_UDP

#include <cstdint>
#include <vector>
#include <Windows.h>
#include "../CRT/mutex/smutex.hpp"
#include <atomic>
#include "data.h"
#include "3rd_party\steam\steam_api.h"
#include "3rd_party\steam\ISteamNetworkingTypes.h"
#include "3rd_party\steam\ISteamNetworkingSockets.h"

namespace connector {

	class data;

	class steam_session {
	public:
#ifdef HAS_CRT
		steam_session(ISteamClient* steam_client, const char* server, uint16_t port, const std::string& token);
#endif
		steam_session(ISteamClient* steam_client,uint32 server, uint16_t port, const std::string& token);
		~steam_session();

		bool send_data(std::vector<connector::data> data, int flags = 0);
		bool send_data(connector::data data, int flags = 0);

		bool isConnected();
		bool sendToken();

		std::vector<data> process();
		std::vector<data> read_data(std::vector<unsigned char>& data);

		std::atomic_bool failed;

	private:
		HSteamNetConnection socket_;
		std::vector<data> updates_;

		void write_packet(const unsigned char* data, size_t size, int flags = 0);

		std::string token_;
		ISteamNetworkingSockets* m_pSteamNetworkingSockets;
	};

}

#ifdef HAS_CRT
	inline std::shared_ptr<connector::steam_session> networking_steam;
	#ifdef WEB_RADAR_FEATURE
		inline std::shared_ptr<connector::steam_session> networking_steam_radar;
	#endif
#else
	inline connector::steam_session* networking_steam;
	#ifdef WEB_RADAR_FEATURE
		inline connector::steam_session* networking_steam_radar;
	#endif
#endif
#endif