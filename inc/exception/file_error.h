#ifndef FILE_ERROR_H
#define FILE_ERROR_H

#include "game_error.h"

class FileError : public GameError {
public:
	explicit FileError(const std::string& desc,
			const std::string& name) noexcept;
	explicit FileError(const FileError& other) noexcept;
	std::string get_filename() const;

private:
	std::string filename;
};

#endif
