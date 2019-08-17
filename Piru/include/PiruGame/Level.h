#pragma once
#include "PiruGame/PiruGameState.h"

class Level {
public:
	Level(PiruGameState*);
	PiruGameState *game;
	virtual void init() = 0;
};

class Level1 : public Level{
public:
	Level1(PiruGameState*);
	void init();
};

