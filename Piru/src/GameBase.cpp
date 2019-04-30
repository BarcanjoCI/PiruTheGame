#include "GameBase.h"
#include <SFML\Audio.hpp>
#include <iostream>

Game::Game() {
	this->currState = 0;
}

void Game::Start() {
	init();
	//this->changeMusic(states[0]->music);
	GameLoop();
}

// loop deals with changing states
void Game::GameLoop() {

	//music.play();
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			states[currState]->update(event);
		}
		states[currState]->updateKeyboard();
		window.clear(sf::Color::Black);

		// Render Everything 
		states[currState]->render(&window);

		window.display();
	}
}

void Game::changeState(unsigned int ID) {
	if (ID < 0 || ID > this->states.size() - 1) {
		std::cout << "Tried to access non-existing game state";
		exit(0);
	}
	this->currState = ID;
	//this->changeMusic(states[ID]->music);
}

void Game::addState(std::shared_ptr<GameState> state) {
	this->states.push_back(state);
}

void Game::changeMusic(std::string string) {
	music.stop();
	if (!music.openFromFile(string)) {
		std::cout << "Could not load Music";
	}
	music.play();
}

GameState::GameState(Game *game) {
	this->game = game;
}

