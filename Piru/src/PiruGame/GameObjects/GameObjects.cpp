#include "PiruGame/GameObjects/GameObjects.h"
#include "PiruGame/PiruGameState.h"

void GameObject::isVisible() {
}

// Obstacle Function definitions
Obstacle::Obstacle() {
	model = sf::RectangleShape(sf::Vector2f(200, 50));
	pos = sf::Vector2f(400, 400);
	model.setPosition(pos);
}

Obstacle::Obstacle(sf::Vector2f pos, PiruGameState* game) {
	texture.loadFromFile("GreenPlatform.png");
	sprite.setPosition(pos);
	sprite.setTexture(texture);
	this->game = game;
	sf::FloatRect hitbox = sprite.getGlobalBounds();

	model = sf::RectangleShape(sf::Vector2f(hitbox.width, hitbox.height));
	model.setFillColor(sf::Color::Blue);
	this->pos = pos;
}

void Obstacle::update() {
	model.setPosition(pos.x - game->camera.worldPos.x, pos.y - game->camera.worldPos.y);
	sprite.setPosition(pos.x - game->camera.worldPos.x, pos.y - game->camera.worldPos.y);
}

void Obstacle::render(sf::RenderWindow *window) {
	window->draw(sprite);
}

void Obstacle::handleCollision(std::weak_ptr<GameObject> other) {

}





