#include "../../inc/exception/file_error.h"

FileError::FileError(const std::string& desc, const std::string& name) noexcept:
	GameError::GameError{desc}, filename{name} {}

FileError::FileError(const FileError& other) noexcept:
	GameError::GameError{other}, filename{other.filename} {}

std::string FileError::get_filename() const {
	return filename;
}
