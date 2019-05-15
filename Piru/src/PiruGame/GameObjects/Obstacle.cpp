#include "PiruGame/GameObjects/Obstacle.h"

Obstacle::Obstacle() {
	model = sf::RectangleShape(sf::Vector2f(200, 50));
	pos = sf::Vector2f(400, 400);
	model.setPosition(pos);
}

Obstacle::Obstacle(sf::Vector2f pos) {
	model = sf::RectangleShape(sf::Vector2f(200, 50));
	this->pos = pos;
	model.setPosition(this->pos);
}

void Obstacle::update() {

}

void Obstacle::render(sf::RenderWindow *window) {
	window->draw(model);
}

void Obstacle::handleCollision(std::weak_ptr<GameObject> other) {

}