#ifndef PARSE_ERROR_H
#define PARSE_ERROR_H

#include "file_error.h"

class ParseError : public FileError {
public:
	explicit ParseError(const std::string& desc, const std::string& name,
					size_t lnum) noexcept;
	explicit ParseError(const ParseError& other) noexcept;
	size_t get_line_num() const;

private:
	size_t line_num;
};

#endif
