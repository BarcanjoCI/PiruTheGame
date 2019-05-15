#pragma once
#include "GameObject.h"
#include "PiruGame/GameObjects/Obstacle.h"

class Player : public GameObject {
public:
	Player();
	void render(sf::RenderWindow *window);
	void update();
	void handleCollision(std::weak_ptr<GameObject>);

	sf::Texture testT;
	sf::Sprite testS;
	float gravity;
	float ground;
	std::weak_ptr<GameObject> onPlat;
};
