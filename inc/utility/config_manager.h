#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include "../interfaces/command_handler.h"
#include "../exception/file_error.h"
#include "../exception/parse_error.h"
#include "../exception/key_bind_error.h"

enum class Difficulty { Easy, Medium, Hard };

class ConfigManager {
public:
	Difficulty difficulty = Difficulty::Easy;
	static ConfigManager& instance() {
		static ConfigManager instance;
		return instance;
	}

	ConfigManager(ConfigManager const&)	= delete;
	void operator=(ConfigManager const&)	= delete;

	void write_config(const std::string& filename);
	void read_config(const std::string& filename);
	InputCommand key_to_command(int key);
	void set_binding(int key, InputCommand command);
	const std::string& res_name(const std::string& res) const;

private:
	ConfigManager() =default;
	void add_parsed_binding(const std::string& name,
			const std::string& val,
			const std::string& filename, size_t line_num);

	std::map<std::string, InputCommand> command_names = {
		{"up", InputCommand::MoveUp},
		{"down", InputCommand::MoveDown},
		{"right", InputCommand::MoveRight},
		{"left", InputCommand::MoveLeft},
		{"action", InputCommand::DoAction},
		{"back", InputCommand::Back}
	};
	std::map<std::string, std::string> resource_names;
	std::map<int, InputCommand> key_bindings;
};

#endif
