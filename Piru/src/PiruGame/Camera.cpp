#include "PiruGame/Camera.h"

Camera::Camera() {
	width = 800;
	height = 600;
}

Camera::Camera(std::weak_ptr<GameObject>, World* world) {
	this->player = player;
	this->world = world;
	width = 800;
	height = 600;
	worldPos = sf::Vector2f(0, 0);
}