#include "PiruGame/GameObjects/Player.h"
#include <iostream>

Player::Player() {
	pos = sf::Vector2f(200, 400);
	vel = sf::Vector2f(0, 0);

	ground = 400;
	speed = 5;
	jumpForce = 0;
	gravity = 0.6;

	testT.loadFromFile("player.png");
	testS.setPosition(pos);
	testS.setTexture(testT);
	testS.scale(0.8f, 0.8f);
}

void Player::render(sf::RenderWindow *window) {
	window->draw(testS);
}

void Player::update() {
	bool pressedW = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		vel = sf::Vector2f(speed, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		vel = sf::Vector2f(-speed, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (jumpForce == 0) {
			jumpForce = 14;
		}
	}

	vel.y -= jumpForce;
	pos += vel;
	testS.setPosition(pos);

	if (pos.y < ground) {
		jumpForce -= gravity;
	}
	
	if (pos.y > ground) {
		jumpForce = 0;
		pos.y = ground;
	}
	
	vel = sf::Vector2f(0, 0);

	if (auto tmp = onPlat.lock()) {
		sf::FloatRect hitbox1 = testS.getGlobalBounds();
		sf::FloatRect hitbox2 = tmp->model.getGlobalBounds();

		if (pos.x + hitbox1.width < tmp->pos.x || pos.x > tmp->pos.x + hitbox2.width) {
			onPlat.reset();
			ground = 400;
		}
	}
}

void Player::handleCollision(std::weak_ptr<GameObject> other) {
	if (auto tmp = other.lock()) {
		sf::FloatRect hitbox1 = testS.getGlobalBounds();
		sf::FloatRect hitbox2 = tmp->model.getGlobalBounds();

		if (typeid(*tmp) == typeid(Obstacle)) {

			if (pos.x + hitbox1.width > tmp->pos.x && pos.x < tmp->pos.x + hitbox2.width) {

				if (pos.y + hitbox1.height < tmp->pos.y && pos.y < tmp->pos.y) {
						ground = tmp->pos.y - hitbox1.height;
						onPlat = other.lock();
				
				}

				else if (pos.y < tmp->pos.y + hitbox2.height && pos.y > tmp->pos.y) {
					pos.y = tmp->pos.y + hitbox2.height;
					jumpForce = -0.1;
				}
			}

			else if (pos.y > tmp->pos.y - hitbox1.height -5 && pos.y < tmp->pos.y + hitbox2.height + hitbox1.height + 5){
				if (pos.x + hitbox1.width + 5 > tmp->pos.x && pos.x < tmp->pos.x + hitbox2.width) {
					pos.x = tmp->pos.x - hitbox1.width - 5;
				}

				else if (pos.x < tmp->pos.x + hitbox2.width + 5 && pos.x + hitbox1.width > tmp->pos.x + hitbox2.width)
					pos.x = tmp->pos.x + 5 + hitbox2.width;
			}
		}
	}

	else return;
}