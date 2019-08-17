#include "PiruGame/Level.h"

Level::Level(PiruGameState *game) {
	this->game = game;
}

Level1::Level1(PiruGameState *game) : Level(game) {
}

// create the level by adding all the game objects to it
void Level1::init() {
	game->objects.push_back(std::make_shared<Obstacle>(sf::Vector2f(500, 400), game));
	game->objects.push_back(std::make_shared<Obstacle>(sf::Vector2f(700, 200), game));
	game->objects.push_back(std::make_shared<Obstacle>(sf::Vector2f(900, 0), game));
	game->objects.push_back(std::make_shared<Obstacle>(sf::Vector2f(850, 100), game));
	game->objects.push_back(std::make_shared<Obstacle>(sf::Vector2f(200, -200), game));
	game->objects.push_back(std::make_shared<Obstacle>(sf::Vector2f(300, -100), game));
	game->objects.push_back(std::make_shared<Obstacle>(sf::Vector2f(350, -300), game));
	game->objects.push_back(std::make_shared<Obstacle>(sf::Vector2f(1000, 50), game));
	game->objects.push_back(std::make_shared<Obstacle>(sf::Vector2f(950, 0), game));
	game->objects.push_back(std::make_shared<Obstacle>(sf::Vector2f(650, 0), game));
}