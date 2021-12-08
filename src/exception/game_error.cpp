#include "../../inc/exception/game_error.h"

GameError::GameError(const std::string& descr) noexcept:
	description{descr} {}

GameError::GameError(const GameError& other) noexcept:
	description{other.description} {}

std::string GameError::what() const {
	return description;
}
