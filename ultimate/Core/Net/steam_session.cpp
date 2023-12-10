#include "config.h"
#ifdef ALLOW_UDP
#include "steam_session.h"
#include "writer.h"
#include "reader.h"
#include "data.h"

#ifdef HAS_CRT
static uint32_t parseIPaddress(const char* server) {
	uint32_t out = 0;
	uint32_t a, b, c, d;
	sscanf(server, "%u.%u.%u.%u", &a, &b, &c, &d);
	out = (uint32_t)(((double)a * pow(2, 24)) + ((double)b * pow(2, 16)) + ((double)c * pow(2, 8)) + (double)d);
	return out;
}
#endif

namespace connector {
#ifdef HAS_CRT
	steam_session::steam_session(ISteamClient* steam_client, const char* server, uint16_t port, const std::string& token) : socket_(INVALID_SOCKET), token_(token), m_pSteamNetworkingSockets(nullptr) {
		updates_.clear();
		failed.store(false);
		SteamNetworkingIPAddr address;
		address.SetIPv4(parseIPaddress(server), port);

		m_pSteamNetworkingSockets = (ISteamNetworkingSockets*)steam_client->GetISteamGenericInterface(1, 1, STEAMNETWORKINGSOCKETS_INTERFACE_VERSION);
		if (!m_pSteamNetworkingSockets) {
			failed.store(true);
			return;
		}

		SteamNetworkingConfigValue_t opt[3];
		opt[0].SetInt32(k_ESteamNetworkingConfig_IP_AllowWithoutAuth, 2); 
		opt[1].SetInt32(k_ESteamNetworkingConfig_Unencrypted, 2);
		opt[2].SetInt32(k_ESteamNetworkingConfig_TimeoutConnected, 600000); //60 sec
		socket_ = m_pSteamNetworkingSockets->ConnectByIPAddress(address, sizeof(opt) / sizeof(SteamNetworkingConfigValue_t), opt);
	}
#endif

	steam_session::steam_session(ISteamClient* steam_client, uint32 server, uint16_t port, const std::string& token) : socket_(-1), token_(token), m_pSteamNetworkingSockets(nullptr) {
		updates_.clear();
		
		failed.store(false);
		SteamNetworkingIPAddr address;
		address.SetIPv4(server, port);

		m_pSteamNetworkingSockets = (ISteamNetworkingSockets*)steam_client->GetISteamGenericInterface(1, 1, STEAMNETWORKINGSOCKETS_INTERFACE_VERSION);
		if (!m_pSteamNetworkingSockets) {
			failed.store(true);
			return;
		}

		SteamNetworkingConfigValue_t opt[3];
		opt[0].SetInt32(k_ESteamNetworkingConfig_IP_AllowWithoutAuth, 2);
		opt[1].SetInt32(k_ESteamNetworkingConfig_Unencrypted, 2);
		opt[2].SetInt32(k_ESteamNetworkingConfig_TimeoutConnected, 600000); //600 sec
		socket_ = m_pSteamNetworkingSockets->ConnectByIPAddress(address, sizeof(opt) / sizeof(SteamNetworkingConfigValue_t), opt);
	}

	steam_session::~steam_session() {
		m_pSteamNetworkingSockets->CloseConnection(socket_, 0, XS("Closing connection!"), true);
	}

	bool steam_session::send_data(std::vector<connector::data> data, int flags) {
		writer writer;
		writer.write(std::make_pair((const connector::data*)data.data(), data.size()));
		write_packet(writer.data(), writer.size(), flags);
		return true;
	}

	bool steam_session::send_data(connector::data data, int flags) {
		writer writer;
		writer.write(std::make_pair((const connector::data*)&data, (size_t)1));
		write_packet(writer.data(), writer.size(), flags);
		return true;
	}

	std::vector<data> steam_session::process() {
		// Receive incoming updates.
		std::vector<connector::data> out_data;
		out_data.clear();
		SteamNetworkingMessage_t* msg[3];

		auto response = m_pSteamNetworkingSockets->ReceiveMessagesOnConnection(socket_, msg, 3);
		if (response > 0) {
			for (int i = 0; i < response; i++) {
				reader reader((const unsigned char*)msg[i]->GetData(), msg[i]->GetSize());
				auto new_data = reader.read<std::vector<connector::data>>();
				//append new_data
				for (auto& iter : new_data) {
					out_data.push_back(iter);
				}
				new_data.clear();
				// always release message
				msg[i]->Release();
			}
		}
		else if (response == -1) {
			failed.store(true);
			LOG(XS("[DEBUG] read_packet: connection handle is invalid!"));
		}
		else if (response == 0) {
			//no data available
		}
		return out_data;
	}

	std::vector<data> steam_session::read_data(std::vector<unsigned char>& data_)
	{
		if (data_.size() > 0) {
			reader reader(data_.data(), data_.size());
			return reader.read<std::vector<data>>();
		}
		else {
			return {};
		}
	}

	void steam_session::write_packet(const unsigned char* data, size_t size, int flags) {
		auto result = m_pSteamNetworkingSockets->SendMessageToConnection(socket_, (void*)data, size, flags, nullptr);
		if (result != k_EResultOK) {
			LOG(XS("[DEBUG] write_packet: Failed to send message EResult: %d"), result);
			SteamConnectorError = true;
			failed.store(true);
			return;
		}
	}

	template<class T>
	T my_ntoh(unsigned char* buf) {
		const auto s = sizeof(T);
		T value = 0;
		for (unsigned i = 0; i < s; i++)
			value |= buf[i] << CHAR_BIT * (s - 1 - i);
		return value;
	}

	bool steam_session::isConnected()
	{
		SteamNetConnectionInfo_t info;
		m_pSteamNetworkingSockets->GetConnectionInfo(socket_, &info);
		if (k_ESteamNetworkingConnectionState_Connected == info.m_eState)
			return true;
		return false;
	}

	bool steam_session::sendToken()
	{
		static bool first_time = true;
		if (first_time) {
			first_time = false;
			const char* data = token_.c_str();
			m_pSteamNetworkingSockets->SendMessageToConnection(socket_, (void*)data, (uint32_t)token_.length() + 1, 0, nullptr);
			return true;
		}
		return false;
	}
}
#endif
