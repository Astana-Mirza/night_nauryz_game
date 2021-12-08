#ifndef KEY_BIND_ERROR_H
#define KEY_BIND_ERROR_H

#include "game_error.h"

class KeyBindError : public GameError {
public:
	explicit KeyBindError(const std::string& descr, int k) noexcept;
	explicit KeyBindError(const KeyBindError& other) noexcept;
	int get_key() const;

private:
	int key;
};

#endif
