#include "PiruGame/PiruGameState.h"
#include "PiruGame/GameObjects/GameObjects.h"

PiruGameState::PiruGameState(Game *game) : GameState(game){
	player = std::make_shared<Player>(this);
	objects.push_back(player);
	camera = Camera(player, &world);
	objects.push_back(std::make_shared<Obstacle>(sf::Vector2f(500, 400), this));
	objects.push_back(std::make_shared<Obstacle>(sf::Vector2f(100, 250), this));
}

void PiruGameState::render(sf::RenderWindow *window) {
	for (int i = 0; i < objects.size(); i++)
		objects[i]->render(window);
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

	for (int i = 0; i < objects.size(); i++)
		objects[i]->update();
}