#pragma once
#include "SFML/Graphics.hpp"
#include <typeinfo>

class PiruGameState;
class GameObject {
public:
	sf::Vector2f pos;
	sf::Vector2f vel;
	float speed;

	PiruGameState* game;

	sf::RectangleShape model;
	sf::Texture texture;
	sf::Sprite sprite;
	bool visible;

	void isVisible();
	virtual void render(sf::RenderWindow *window) = 0;
	virtual void update() = 0;
	virtual void handleCollision(std::weak_ptr<GameObject>) = 0;
};

class Obstacle : public GameObject {
public:
	Obstacle();
	Obstacle(sf::Vector2f pos, PiruGameState*);
	void render(sf::RenderWindow *window);
	void update();
	void handleCollision(std::weak_ptr<GameObject>);
};

class Ability : public GameObject {
public:

	int type; 
	float damage, range, cooldown;

	virtual void render(sf::RenderWindow *window) = 0;
	virtual void update() = 0;
	virtual void handleCollision(std::weak_ptr<GameObject>) = 0;
};

enum Facing {LEFT, RIGHT, UP, DOWN};

class Character : public GameObject {
public:
	std::vector<sf::Clock> cooldowns;
	float maxHP, currHP, maxMana, currMana;
	Facing facing;
	float jumpForce;
};


