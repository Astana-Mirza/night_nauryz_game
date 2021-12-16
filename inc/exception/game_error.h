#ifndef GAME_ERROR_H
#define GAME_ERROR_H

#include <string>

class GameError {
public:
	explicit GameError(const std::string& descr) noexcept;
	explicit GameError(const GameError& other) noexcept;
	std::string what() const;
	virtual ~GameError() =default;

private:
	std::string description;
};

#endif
