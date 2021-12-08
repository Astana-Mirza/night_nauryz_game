#include "../../inc/exception/key_bind_error.h"

KeyBindError::KeyBindError(const std::string& descr, int k) noexcept:
	GameError::GameError{descr}, key{k} {}

int KeyBindError::get_key() const {
	return key;
}
