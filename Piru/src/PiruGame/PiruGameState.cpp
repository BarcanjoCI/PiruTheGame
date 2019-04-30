#include "PiruGame/PiruGameState.h"
#include "PiruGame/GameObjects/Player.h"

PiruGameState::PiruGameState(Game *game) : GameState(game){
	player = std::make_shared<Player>();
	objects.push_back(player);
}

void PiruGameState::render(sf::RenderWindow *window) {
	for (auto it = objects.begin(); it != objects.end(); it++)
		(*it)->render(window);
}

void PiruGameState::update(sf::Event event) {
	
}

void PiruGameState::updateKeyboard() {
	for (auto it = objects.begin(); it != objects.end(); it++)
		(*it)->update();
}