#pragma once
#include "GameObject.h"

class Obstacle : public GameObject {
public:
	Obstacle();
	Obstacle(sf::Vector2f pos);
	void render(sf::RenderWindow *window);
	void update();
	void handleCollision(std::weak_ptr<GameObject>);
};