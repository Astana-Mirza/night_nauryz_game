#include "../../inc/utility/config_manager.h"

void ConfigManager::read_config(const std::string& filename) {
	resource_names = {};
	key_bindings = {};
	std::ifstream conf(filename, std::ios::in);
	bool controls = true;
	if (conf.is_open()) {
		std::string line;
		while (std::getline(conf, line)) {
			std::remove_if(line.begin(), line.end(),
				[](char c)->bool { return std::isspace(c); });
			if (line.empty())
				continue;
			if (line == "[controls]")
				controls = true;
			else if (line == "[resources]")
				controls = false;
			else {
				auto eq_pos = line.find('=');
				auto name = line.substr(0, eq_pos);
				auto val = line.substr(eq_pos+1);
				if (controls)
					key_bindings[std::stoi(val)] =
							command_names[name];
				else
					resource_names[name] = val;
			}
		}
		conf.close();
	}
	else
		throw std::runtime_error{
			"unable to open file"};
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
		throw std::runtime_error{
			"unable to open file"};
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
