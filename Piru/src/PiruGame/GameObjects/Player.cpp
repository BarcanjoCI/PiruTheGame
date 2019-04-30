#include "PiruGame/GameObjects/Player.h"

Player::Player() {
	pos = sf::Vector2f(200, 200);
	vel = sf::Vector2f(1, 0);
	model = sf::RectangleShape(pos);
	model.setPosition(pos);
}

void Player::render(sf::RenderWindow *window) {
	window->draw(model);
}

void Player::update() {
	pos += vel;
	model.setPosition(pos);
}