#pragma once

#include <string>
#include <vector>
#include "../CRT/mutex/smutex.hpp"
#include "singleton.h"

#define SERIALIZE(json, x) Config::serialize(json, XS(#x), x);
#define PARSE(json, x) Config::parse(json, XS(#x), x);

//Some parts are disabled due to missing config implementation, you can use any config format. This is just an example that works in ricochets' cheat

class Config : public Singleton<Config> {
public:
	Config();

	void load_config_data(const std::vector<unsigned char>& data);
	std::vector<unsigned char> get_config_data();
	void save_config();
	void save_new_config(std::string name, bool is_public);
	void remove_config();
	void change_public_status(bool new_state, bool is_locked = false);
	void refresh_list();
	void request_selected_config();

	void clear_list(const bool lock = true) {
		if (lock) {
			list_lock.lock();
			list.clear();
			list_lock.unlock();
		}
		else {
			list.clear();
		}
#if 0
		options.listbox.find_or_default("Config list")->ClearEntryList();
		options.listbox.find_or_default("Config list")->SetIndex(0);
#endif
		selected_config = 0;
	}

	void update_list_from_net(const bool lock = true)
	{
		if (lock) {
			list_lock.lock();
		}
#if 0
		auto list_box = options.listbox.find_or_default("Config list");
		list_box->ClearEntryList();

		for (auto& iter : list) {
			list_box->AddEntry(iter.name + " (id:" + std::to_string(iter.id) + ")");
		}

		if (list_box->GetIndex() > list.size())
			list_box->SetIndex(0);

#endif
		if (lock) {
			list_lock.unlock();
		}
	}

	void set_user_id(std::string id) {
		my_user_id = id;
	}

	void update_public_status(uint32_t id, bool is_public) {
		list_lock.lock();

		for (auto& iter : list) {
			if (iter.id != id)
				continue;

			iter.is_public = is_public;
			break;
		}
		list_lock.unlock();
	}

	void add_config_info(uint32_t id, std::string name, std::string owner, bool is_public) {
		config_list cfg;
		cfg.id = id;
		cfg.name = name;
		cfg.is_public = is_public;
		cfg.can_save = owner == my_user_id ? true : false;
		list_lock.lock();
		bool found = false;
		for (auto& iter : list) {
			if (iter.id != cfg.id)
				continue;

			iter.name = cfg.name;
			iter.is_public = cfg.is_public;
			iter.can_save = cfg.can_save;
			iter.owner = cfg.owner;
			found = true;
			break;
		}

		if (found)
		{
			list_lock.unlock();
			return;
		}
		list.push_back(cfg);
		list_lock.unlock();
	}

	size_t selected_config = 0;
	rb::smutex list_lock;

	struct config_list {
		uint32_t id;
		bool can_save;
		bool is_public;
		std::string name;
		std::string owner;
	};

private:
	std::vector<config_list> list;
	std::string my_user_id;
};