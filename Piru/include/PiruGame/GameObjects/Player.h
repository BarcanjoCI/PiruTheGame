#pragma once
#include "GameObject.h"

class Player : public GameObject {
public:
	Player();
	void render(sf::RenderWindow *window);
	void update();
	sf::RectangleShape model;
};