#pragma once

#include "..\Includes\includes.hpp"

//ISteamNetworkingSockets
#include "3rd_party\steam\ISteamNetworkingSockets.h"

//Xoring strings
#include "..\Utils\xorstr.hpp"
//or replace _ macro or use dummy one
#define _(x) XS(s)

//additional includes

#define IP "149.202.51.151"
#define PORT 8879
#ifdef DEBUG_MODE 
#define TOKEN "xp5296OQsoi1SiId9wMn3EffpQfrst88"
#else
static const unsigned char TOKEN[] = { 0x21, 0x11, 0x15, 0xCD, 0x32, 0x64, 0xFA, 0x6C, 0x78, 0x3A, 0x97, 0x9A, 0xCC, 0xFF, 0x32, 0x64, 0x42, 0xBB, 0xDA, 0xB2, 0xDD, 0xAA, 0x24, 0x25, 0xCC, 0xCA, 0xFA, 0xD8, 0x16, 0xC3, 0x57, 0xD2, 0xA2 };
#endif


#define ALLOW_UDP

#define SUPPORTS_COMPRESSION 
#define CONFIG_FEATURE

#define SHARED_ESP_DATA_SIZE_LIMIT 1024

//GAME IDS
#define CSGO 1 << 0
#define RUST 1 << 1
#define APEX 1 << 2
#define EFT  1 << 3

#define CURRENT_GAME RUST