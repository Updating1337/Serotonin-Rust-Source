#include "data.h"

namespace connector {

	static file readFile(reader& reader) {
		file values;
		values.name = reader.read<std::string>();
		values.compressed = (bool)reader.read<uint8_t>();
		values.size_without_compression = reader.read<uint32_t>();
		values.size = reader.read<uint32_t>();
		for (unsigned int i = 0; i < values.size; i++) {
			values.data.push_back(reader.read<unsigned char>());
		}
		return values;
	}

	data read_traits<data>::read(reader& reader) {
		auto data_type = reader.read<std::uint32_t>();

		if (data_type == (uint32_t)data::type::FILE) {
			return data(readFile(reader));
		}

		if (data_type == (uint32_t)data::type::SHARED_ESP) {
			shared_esp_data values;
			values.channel = reader.read<uint32_t>();
			auto size = reader.read<uint32_t>();
			if (size > SHARED_ESP_DATA_SIZE_LIMIT)
			{
				invalid test;
				return data(test);
			}

			values.data.resize(size);
			reader.read_bytes(values.data.data(), values.data.size());
			return data(values);
		}

		if (data_type == (uint32_t)data::type::REPORT) {
			report values;
			values.id = reader.read<std::string>();
			values.extra = reader.read<std::string>();
			values.hwid = reader.read<std::string>();
			values.has_file = (bool)reader.read<uint8_t>();
			if (values.has_file) {
				values.file_ = readFile(reader);
			}
			return data(values);
		}

		if (data_type == (uint32_t)data::type::OFFSETS) {
			offsets values;
			values.action = (offset_action)reader.read<uint8_t>();
			values.hash = reader.read<uint32_t>();
			values.name = reader.read<std::string>();
			values.value = reader.read<uint64_t>();
			values.game = reader.read<uint16_t>();
			values.base_index = reader.read<uint32_t>();

			return data(values);
		}

		if (data_type == (uint32_t)data::type::MESSAGE) {
			cheat_message values;
			values.msg = (messages)reader.read<uint8_t>();
			values.value = reader.read<std::string>();
			values.value_int = reader.read<uint32_t>();
			return data(values);
		}

		if (data_type == (uint32_t)data::type::SLICED_DATA) {
			sliced_data values;
			values.packet_id = reader.read<uint32_t>();
			values.slice_index = reader.read<uint16_t>();
			values.max_slices = reader.read<uint16_t>();
			values.data.resize(reader.read<uint32_t>(), 0);
			reader.read_bytes(values.data.data(), values.data.size());
			return data(values);
		}
#ifdef CONFIG_FEATURE
		if (data_type == (uint32_t)data::type::CLOUD_CONFIG) {
			cloud_config values;
			values.action = (cloud_action)reader.read<uint32_t>();
			values.config_id = reader.read<uint32_t>();
			values.config_name = reader.read<std::string>();
			values.data.resize(reader.read<uint32_t>(), 0);
			reader.read_bytes(values.data.data(), values.data.size());
			values.is_public = (bool)reader.read<uint8_t>();
			values.user_id = reader.read<std::string>();
			return data(values);
		}
#endif
#ifdef CSGO_STRUCTS
		if (data_type == (uint32_t)data::type::WEB_RADAR) {
			web_radar_info values;
			values.share_code_hash = reader.read<uint32_t>();
			values.map = reader.read<std::string>();
			values.players_size = reader.read<uint16_t>();
			values.players.resize(values.players_size);
			for (uint16_t i = 0; i < values.players_size; i++) {
				values.players[i].name = reader.read<std::string>();
				values.players[i].weap_id = reader.read<uint16_t>();
				reader.read_bytes((unsigned char*)(&values.players[i].x), sizeof(float));
				reader.read_bytes((unsigned char*)(&values.players[i].y), sizeof(float));
				reader.read_bytes((unsigned char*)(&values.players[i].angle), sizeof(float));
				values.players[i].steamid = reader.read<std::string>();
				values.players[i].hp = reader.read<uint16_t>();
				values.players[i].team = reader.read<uint16_t>();
			}
			reader.read_bytes((unsigned char*)(&values.bomb_x), sizeof(float));
			reader.read_bytes((unsigned char*)(&values.bomb_y), sizeof(float));
			values.bomb_time = reader.read<uint32_t>();
			values.nades_size = reader.read<uint16_t>();
			values.nades.resize(values.nades_size);
			for (uint16_t i = 0; i < values.nades_size; i++) {
				values.nades[i].type = reader.read<uint16_t>();
				reader.read_bytes((unsigned char*)(&values.nades[i].x), sizeof(float));
				reader.read_bytes((unsigned char*)(&values.nades[i].y), sizeof(float));
			}

			return data(values);
		}
#endif

		invalid test;
		return data(test);
	}

	static void writeFile(writer& writer, const file& values) {
		writer.write(values.name.c_str());
		writer.write((uint8_t)values.compressed);
		writer.write((uint32_t)values.size_without_compression);
		writer.write((uint32_t)values.size);
		for (auto& iter : values.data) {
			writer.write((unsigned char)iter);
		}
	}

	void write_traits<data>::write(writer& writer, const data& data_) {
		auto data_type = data_.get_type();
		writer.write((std::uint32_t)data_type);

		if (data_type == data::type::FILE) {
			auto& values = std::get<file>(data_.data_struct_);
			writeFile(writer, values);
		}

		if (data_type == data::type::SHARED_ESP) {
			auto& values = std::get<shared_esp_data>(data_.data_struct_);
			writer.write(values.channel);
			writer.write((uint32_t)values.data.size());
			writer.write_bytes(values.data.data(), values.data.size());
		}

		if (data_type == data::type::REPORT) {
			auto& values = std::get<report>(data_.data_struct_);
			writer.write(values.id.c_str());
			writer.write(values.extra.c_str());
			writer.write(values.hwid.c_str());
			writer.write((uint8_t)values.has_file);
			if (values.has_file) {
				writeFile(writer, values.file_);
			}
		}

		if (data_type == data::type::OFFSETS) {
			auto& values = std::get<offsets>(data_.data_struct_);
			writer.write((uint8_t)values.action);
			writer.write(values.hash);
			writer.write(values.name.c_str());
			writer.write(values.value);
			writer.write(values.game);
			writer.write(values.base_index);
		}

		if (data_type == data::type::MESSAGE) {
			auto& values = std::get<cheat_message>(data_.data_struct_);
			writer.write((uint8_t)values.msg);
			writer.write(values.value.c_str());
			writer.write((uint32_t)values.value_int);
		}

		if (data_type == data::type::SLICED_DATA) {
			auto& values = std::get<sliced_data>(data_.data_struct_);
			writer.write((uint32_t)values.packet_id);
			writer.write((uint16_t)values.slice_index);
			writer.write((uint16_t)values.max_slices);
			writer.write((uint32_t)values.data.size());
			writer.write_bytes(values.data.data(), values.data.size());
		}
#ifdef CONFIG_FEATURE
		if (data_type == data::type::CLOUD_CONFIG) {
			auto& values = std::get<cloud_config>(data_.data_struct_);
			writer.write((uint32_t)values.action);
			writer.write(values.config_id);
			writer.write(values.config_name.c_str());
			writer.write((uint32_t)values.data.size());
			writer.write_bytes(values.data.data(), values.data.size());
			writer.write((uint8_t)values.is_public);
			writer.write(values.user_id.c_str());
		}
#endif
#ifdef CSGO_STRUCTS
		if (data_type == data::type::WEB_RADAR) {
			auto& values = std::get<web_radar_info>(data_.data_struct_);
			writer.write(values.share_code_hash);
			writer.write(values.map.c_str());
			writer.write(values.players_size);
			for (auto& iter : values.players) {
				writer.write(iter.name.c_str());
				writer.write(iter.weap_id);
				writer.write_bytes((const unsigned char*)(&iter.x), sizeof(float));
				writer.write_bytes((const unsigned char*)(&iter.y), sizeof(float));
				writer.write_bytes((const unsigned char*)(&iter.angle), sizeof(float));
				writer.write(iter.steamid.c_str());
				writer.write(iter.hp);
				writer.write(iter.team);
			}
			writer.write_bytes((const unsigned char*)(&values.bomb_x), sizeof(float));
			writer.write_bytes((const unsigned char*)(&values.bomb_y), sizeof(float));
			writer.write(values.bomb_time);
			writer.write(values.nades_size);
			for (auto& iter : values.nades) {
				writer.write(iter.type);
				writer.write_bytes((const unsigned char*)(&iter.x), sizeof(float));
				writer.write_bytes((const unsigned char*)(&iter.y), sizeof(float));
			}
		}
#endif
	}
}