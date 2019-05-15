#include "PiruGame/PiruGameState.h"
#include "PiruGame/GameObjects/Player.h"
#include "PiruGame/GameObjects/Obstacle.h"

PiruGameState::PiruGameState(Game *game) : GameState(game){
	player = std::make_shared<Player>();
	objects.push_back(player);
	objects.push_back(std::make_shared<Obstacle>(sf::Vector2f(500, 400)));
	objects.push_back(std::make_shared<Obstacle>(sf::Vector2f(100, 250)));
}

void PiruGameState::render(sf::RenderWindow *window) {
	for (auto it = objects.begin(); it != objects.end(); it++)
		(*it)->render(window);
}

void PiruGameState::update(sf::Event event) {
}

void PiruGameState::updateKeyboard() {

	for (unsigned int i = 0; i < objects.size(); i++) {
		for (unsigned int o = i + 1; o < objects.size(); o++) {
			objects.at(i)->handleCollision(objects.at(o));
			objects.at(o)->handleCollision(objects.at(i));
		}
	}

	for (auto it = objects.begin(); it != objects.end(); it++) {
		(*it)->update();
	}
}