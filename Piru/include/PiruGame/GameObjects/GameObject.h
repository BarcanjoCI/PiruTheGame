#pragma once
#include "SFML/Graphics.hpp"
#include <typeinfo>

class GameObject {
public:
	sf::Vector2f pos;
	sf::Vector2f vel;
	float speed;
	float jumpForce;
	sf::RectangleShape model;

	virtual void render(sf::RenderWindow *window) = 0;
	virtual void update() = 0;
	virtual void handleCollision(std::weak_ptr<GameObject>) = 0;
};


