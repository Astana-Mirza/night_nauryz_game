#include "../../inc/utility/config_manager.h"

void ConfigManager::read_config(const std::string& filename) {
	resource_names = {};
	key_bindings = {};
	std::ifstream conf(filename, std::ios::in);
	size_t line_num = 1;
	bool controls = true;
	if (conf.is_open()) {
		std::string line;
		while (std::getline(conf, line)) {
			auto new_end = std::remove_if(line.begin(), line.end(),
				[](char c){ return std::isspace(c); });
			line.erase(new_end, line.end());
			if (line.empty())
				continue;
			if (line == "[controls]")
				controls = true;
			else if (line == "[resources]")
				controls = false;
			else {
				auto eq_pos = line.find('=');
				if (eq_pos == line.size()-1)
					throw ParseError{"missing \"=\"",
							filename, line_num};
				auto name = line.substr(0, eq_pos);
				auto val = line.substr(eq_pos+1);
				if (name.empty() || val.empty())
					throw ParseError{"missing name or value",
						filename, line_num};
				if (controls) {
					add_parsed_binding(name, val,
							filename, line_num);
				} else {
					resource_names[name] = val;
				}
			}
			line_num++;
		}
		conf.close();
	}
	else
		throw FileError{"unable to open file", filename};
}


void ConfigManager::write_config(const std::string& filename) {
	std::ofstream conf(filename, std::ios::out);
	if (conf.is_open()) {
		conf << "[controls]\n";
		for (auto& [name, command] : command_names) {
			for (auto [key, key_comm] : key_bindings) {
				if (command == key_comm) {
					conf << name << '=' << key << '\n';
				}
			}
		}
		conf << "[resources]\n";
		for (auto& [name, res] : resource_names)
			conf << name << '=' << res << '\n';
		conf.close();
	}
	else
		throw FileError{"unable to open file", filename};
}


InputCommand ConfigManager::key_to_command(int key) {
	return key_bindings[key];
}


const std::string& ConfigManager::res_name(const std::string& res) const {
	return resource_names.at(res);
}


void ConfigManager::set_binding(int key, InputCommand command) {
	for (auto [key, key_comm] : key_bindings) {
		if (command == key_comm)
			key_bindings.erase(key);
	}
	key_bindings[key] = command;
}


void ConfigManager::add_parsed_binding(const std::string& name,
				const std::string& val,
				const std::string& filename, size_t line_num) {
	if (!std::all_of(val.begin(), val.end(), [](char c)->bool {
		return std::isdigit(c);
	}))
		throw ParseError{"must be a number after \"=\"",
				filename, line_num};
	int key = std::stoi(val);
	if (key_bindings.contains(key))
		throw KeyBindError{"attempt to bind key twice", key};
	if (!command_names.contains(name))
		throw KeyBindError{"unknown command: " + name, key};
	key_bindings[key] = command_names[name];
}
