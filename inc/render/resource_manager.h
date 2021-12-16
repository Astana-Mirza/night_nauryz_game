#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include "../exception/file_error.h"

template <typename Resource>
class ResourceManager {
public:
	static ResourceManager& instance() {
		static ResourceManager instance;
		return instance;
	}

	ResourceManager(ResourceManager const&)	= delete;
	void operator=(ResourceManager const&)	= delete;


	const Resource& get(const std::string& name) {
		if (resources.find(name) == resources.end()) {
			load_from_file(name);
		}
		return resources.at(name);
	}


	void load_from_file(const std::string& name) {
		if (!resources[name].loadFromFile(name)) {
			throw FileError{
				"cannot load resource from file ", name};
		}
	}

private:
	ResourceManager() = default;
	std::map<std::string, Resource> resources;
};

#endif
