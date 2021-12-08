#include "../../inc/exception/parse_error.h"

ParseError::ParseError(const std::string& desc, const std::string& name,
	size_t lnum) noexcept:
	FileError::FileError(desc, name), line_num{lnum} {}

ParseError::ParseError(const ParseError& other) noexcept:
	FileError::FileError(other), line_num{other.line_num} {}

size_t ParseError::get_line_num() const {
	return line_num;
}
