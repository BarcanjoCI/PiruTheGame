#pragma once
#include "PiruGame/GameObjects/Player.h"
#include "World.h"

class Camera {
public:
	Camera();
	Camera(std::weak_ptr<GameObject>, World*);
	Player *player;
	World *world;

	float width, height;
	sf::Vector2f worldPos;
};