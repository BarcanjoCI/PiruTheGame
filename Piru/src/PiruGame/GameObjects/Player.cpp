#include "PiruGame/GameObjects/Player.h"
#include <iostream>
#include "PiruGame/PiruGameState.h"
#include <algorithm>

BasicAttack::BasicAttack(Player *player) {
	this->player = player;
	texture.loadFromFile("BasicAttack.png");
	sprite.setTexture(texture);
	hitbox = sprite.getGlobalBounds();
	animationTime.restart();
	alive = true;

	if (player->facing == LEFT) {
		sprite.setTextureRect(sf::IntRect(24, 0, -24, 26));
	}

	sprite.scale(2.0f, 2.0f);
}

void BasicAttack::render(sf::RenderWindow *window) {
	window->draw(sprite);
}

void BasicAttack::update() {
	pos = player->pos;
	if(player->facing == RIGHT)
		sprite.setPosition(pos.x - player->game->camera.worldPos.x - 2, pos.y - player->game->camera.worldPos.y -20);

	else if (player->facing == LEFT) 
		sprite.setPosition(pos.x - player->game->camera.worldPos.x - 24, pos.y - player->game->camera.worldPos.y - 20);


	if (animationTime.getElapsedTime().asSeconds() > 0.3)
		alive = false;
}

void BasicAttack::handleCollision(std::weak_ptr<GameObject>) {

}

BlueBlast::BlueBlast(Player* player) {

	speed = 10;
	cooldown = 1;
	this->player = player;
	
	texture.loadFromFile("BlueBlast.png");
	sprite.setTexture(texture);
	hitbox = sprite.getGlobalBounds();

	if (player->facing == LEFT) {
		pos=sf::Vector2f(player->pos.x - 20, player->pos.y + 8);
		speed *= -1;
	}

	else if (player->facing == RIGHT) {
		pos = sf::Vector2f(player->pos.x + 20, player->pos.y + 8);
	}

	vel = sf::Vector2f(speed, 0);
}

void BlueBlast::update() {
	pos += vel;
	sprite.setPosition(pos);
	sprite.setPosition(pos.x - player->game->camera.worldPos.x, pos.y - player->game->camera.worldPos.y);
}

void BlueBlast::render(sf::RenderWindow* window) {
	window->draw(sprite);
}

void BlueBlast::handleCollision(std::weak_ptr<GameObject>) {

}

Player::Player(PiruGameState* game) {
	this->game = game;
	cooldowns.push_back(sf::Clock());
	cooldowns.push_back(sf::Clock());

	pos = sf::Vector2f(400, 400);
	vel = sf::Vector2f(0, 0);

	
	lastSpellUsed = 0;
	casting = false;
	ground = 400;
	speed = 5;
	jumpForce = 0;
	gravity = 0.6;
	facing = RIGHT;

	texture.loadFromFile("player.png");
	sprite.setPosition(pos);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 10, 11, 16));
	sprite.scale(2.0f, 2.0f);
	hitbox = sprite.getGlobalBounds();
}

void Player::render(sf::RenderWindow *window) {
	window->draw(sprite);
}

void Player::update() {
	bool pressedW = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		vel = sf::Vector2f(speed, 0);
		if (!facing == RIGHT && !casting) {
			sprite.setTextureRect(sf::IntRect(0, 10, 11, 16));
			facing = RIGHT;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		vel = sf::Vector2f(-speed, 0);
		if (!facing == LEFT && !casting) {
			sprite.setTextureRect(sf::IntRect(11, 10, -11, 16));
			facing = LEFT;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (jumpForce == 0) {
			jumpForce = 14;
		}
	}

	vel.y -= jumpForce;
	pos += vel;

	if (game->camera.locked)
		sprite.setPosition(pos);
	else
		game->camera.worldPos = sf::Vector2f(pos.x - 400, pos.y -400);
	
	if (pos.y < ground) {
		jumpForce -= gravity;
	}
	
	if (pos.y > ground) {
		jumpForce = 0;
		pos.y = ground;
	}
	
	vel = sf::Vector2f(0, 0);

	if (auto tmp = onPlat.lock()) {

		if (pos.x + hitbox.width < tmp->pos.x || pos.x > tmp->pos.x + tmp->hitbox.width) {
			onPlat.reset();
			ground = 400;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
		if (cooldowns.at(0).getElapsedTime().asSeconds() > 0.5 && !casting) {
			if (facing == RIGHT) {
				sprite.setTextureRect(sf::IntRect(11, 10, 19, 24));
			}

			else if(facing == LEFT)
				sprite.setTextureRect(sf::IntRect(30, 10, -19, 24));
			game->objects.push_back(std::make_shared<BlueBlast>(this));
			cooldowns.at(0).restart();
			lastSpellUsed = 0;
			casting = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		if (cooldowns.at(1).getElapsedTime().asSeconds() > 0.5 && !casting) {
			if (facing == RIGHT) {
				sprite.setTextureRect(sf::IntRect(32, 10, 11, 16));
			}

			else if (facing == LEFT) {
				sprite.setTextureRect(sf::IntRect(43, 10, -11, 16));
			}
			game->objects.push_back(std::make_shared<BasicAttack>(this));
			cooldowns.at(1).restart();
			lastSpellUsed = 1;
			casting = true;
		}
	}

	if (casting && cooldowns.at(lastSpellUsed).getElapsedTime().asSeconds() > 0.3){
		if(facing==RIGHT)
			sprite.setTextureRect(sf::IntRect(0, 10, 11, 16));
		if(facing == LEFT)
			sprite.setTextureRect(sf::IntRect(11, 10, -11, 16));
		casting = false;

	}
}

void Player::handleCollision(std::weak_ptr<GameObject> other) {
	if (auto tmp = other.lock()) {
		if (typeid(*tmp) == typeid(Obstacle)) {

			if (pos.x + hitbox.width > tmp->pos.x && pos.x < tmp->pos.x + tmp->hitbox.width) {
		
				if (pos.y + hitbox.height < tmp->pos.y && pos.y < tmp->pos.y) {
					if (tmp->pos.y - hitbox.height < ground) {
						ground = tmp->pos.y - hitbox.height;
						onPlat = other.lock();
					}
				}

				else if (pos.y < tmp->pos.y + tmp->hitbox.height && pos.y > tmp->pos.y) {
					pos.y = tmp->pos.y + tmp->hitbox.height;
					jumpForce = -0.1;
				}
			}

			else if (pos.y > tmp->pos.y - hitbox.height && pos.y < tmp->pos.y + tmp->hitbox.height + hitbox.height){
				if (pos.x + hitbox.width + 5 > tmp->pos.x && pos.x < tmp->pos.x + tmp->hitbox.width) {
					pos.x = tmp->pos.x - hitbox.width - 5;
				}

				else if (pos.x < tmp->pos.x + tmp->hitbox.width + 5 && pos.x + hitbox.width > tmp->pos.x + tmp->hitbox.width) {
					pos.x = tmp->pos.x + 5 + tmp->hitbox.width;
				}
			}
		}
	}
	else return;
}