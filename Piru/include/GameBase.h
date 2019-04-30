#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
#include <string>

class GameState;

// Create game application by extending this class
class Game {
public:
	Game(); // Initializes the game object and the its window to default values
	void Start(); // starts the main game loop

	// Change the game state to the number provided
	// if the number is invalid (i.e negative or bigger than number of states-1) exits the program
	void changeState(unsigned int ID);

	// Add a state to the game
	// THE ORDER WHICH YOU ADD THEM IS IMPORTANT, first will be 0, second will be 1 and so on
	void addState(std::shared_ptr<GameState> state);

	void changeMusic(std::string music);



protected:
	// This function must be implemented by the game that extends this class
	// For example, Use it to initialize and add your game states to the game app
	virtual void init() = 0;

	sf::RenderWindow window;

private:
	std::vector<std::shared_ptr<GameState>> states;
	unsigned int currState;
	sf::Music music;

	void GameLoop(); // game loop according to sfml
};

// Create game states by extending this class
class GameState {
public:
	GameState(Game *game);

	// The render function deals with allt he rendering that must be done to the screen
	// Takes a reference to the SFML window that is to be drawn to
	virtual void render(sf::RenderWindow *window) = 0;

	// The update function deals with input and changes in the data models accordingly
	// Takes a SFML event so it can check for single presses, the keyboard can be accessed anywhere
	virtual void update(sf::Event event) = 0;

	virtual void updateKeyboard() = 0;
	std::string music;

protected:
	Game *game;
};