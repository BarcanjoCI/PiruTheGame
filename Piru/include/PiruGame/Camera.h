#pragma once
#include "PiruGame/GameObjects/Player.h"

class Camera {
public:
	Camera();
	Camera(std::weak_ptr<GameObject>);
	Player *player;
	
	bool locked;
	float width, height;
	sf::Vector2f worldPos;
};