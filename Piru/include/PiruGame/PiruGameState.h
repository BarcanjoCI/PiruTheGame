#pragma once
#include "GameBase.h"
#include "GameObjects/GameObject.h"

/*
This class is the main game state - Where the game is going to play out.
*/
class PiruGameState : public GameState {
public:
	PiruGameState(Game *game);
	void render(sf::RenderWindow *window);
	void update(sf::Event event);
	void updateKeyboard();

	std::vector<std::shared_ptr<GameObject>> objects;
	std::shared_ptr<GameObject> player;
};