#ifndef WALL_ERROR_H
#define WALL_ERROR_H

#include "game_error.h"

class WallError : public GameError {
public:
	using GameError::GameError;
};

#endif
