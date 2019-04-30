#pragma once
#include "SFML/Graphics.hpp"

class GameObject {
public:
	sf::Vector2f pos;
	sf::Vector2f vel;

	virtual void render(sf::RenderWindow *window) = 0;
	virtual void update() = 0;
};


