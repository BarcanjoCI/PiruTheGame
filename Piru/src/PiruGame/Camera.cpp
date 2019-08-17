#include "PiruGame/Camera.h"

Camera::Camera() {
	width = 800;
	height = 600;
}

Camera::Camera(std::weak_ptr<GameObject>) {
	this->player = player;
	width = 800;
	height = 600;
	locked = false;
	worldPos = sf::Vector2f(0, 0);
}