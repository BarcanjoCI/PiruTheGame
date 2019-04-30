#include "Piru/Piru.h"
#include "PiruGame/PiruGameState.h"

void Piru::init() {
	addState(std::make_shared<PiruGameState>(this));

	window.create(sf::VideoMode(800, 600), "Piru");
	window.setVerticalSyncEnabled(true);
}