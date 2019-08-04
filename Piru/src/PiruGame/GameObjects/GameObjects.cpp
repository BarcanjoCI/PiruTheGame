#include "PiruGame/GameObjects/GameObjects.h"
#include "PiruGame/PiruGameState.h"

void GameObject::isVisible() {
}

// Obstacle Function definitions
Obstacle::Obstacle() {
}

Obstacle::Obstacle(sf::Vector2f pos, PiruGameState* game) {
	texture.loadFromFile("GreenPlatform.png");
	sprite.setPosition(pos);
	sprite.setTexture(texture);
	this->game = game;
	hitbox = sprite.getGlobalBounds();
	this->pos = pos;
}

void Obstacle::update() {
	sprite.setPosition(pos.x - game->camera.worldPos.x, pos.y - game->camera.worldPos.y);
}

void Obstacle::render(sf::RenderWindow *window) {
	window->draw(sprite);
}

void Obstacle::handleCollision(std::weak_ptr<GameObject> other) {
}





