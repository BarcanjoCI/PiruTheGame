#include "PiruGame/PiruGameState.h"
#include "PiruGame/GameObjects/GameObjects.h"
#include <iostream>
#include <algorithm>

PiruGameState::PiruGameState(Game *game) : GameState(game){
	player = std::make_shared<Player>(this);
	objects.push_back(player);
	camera = Camera(player);
	levels.push_back(std::make_unique<Level1>(this));
	levels.at(0)->init();
}

void PiruGameState::render(sf::RenderWindow *window) {
	// Artifical ground and sky just for now
	sf::RectangleShape sky, ground;
	sky.setSize(sf::Vector2f(800, 2200 + player->hitbox.height));
	sky.setFillColor(sf::Color::Cyan);
	sky.setPosition(0, 0 + camera.worldPos.y);

	ground.setSize(sf::Vector2f(800, 600));
	ground.setFillColor(sf::Color::Green);
	ground.setPosition(0, 400 + player->hitbox.height - camera.worldPos.y);
	window->draw(sky);
	window->draw(ground);
	

	for (int i = 0; i < objects.size(); i++) {
		objects[i]->visible = false;
		if (objects[i]->pos.x < camera.worldPos.x + 800) { // x pos is smaller than left limit
			if (objects[i]->pos.x + objects[i]->hitbox.width > camera.worldPos.x) { // x pos + width is bigger than left limit
				if (objects[i]->pos.y < camera.worldPos.y + 600) {
					if (objects[i]->pos.y + objects[i]->hitbox.height > camera.worldPos.y)
						objects[i]->visible = true;
				}
			}
		}
		if(objects[i]->visible)
			objects[i]->render(window);
	}	
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

	for (int i = 0; i < objects.size(); i++) {
		objects[i]->update();
		if (!objects[i]->alive)
			objects.erase(std::remove(objects.begin(), objects.end(), objects[i]), objects.end());
	}
		
}