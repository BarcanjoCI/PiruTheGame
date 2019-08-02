#pragma once
#include "PiruGame/GameObjects/GameObjects.h"

class Player;

class BlueBlast : public Ability {
public:
	BlueBlast(Player*);
	void render(sf::RenderWindow *window);
	void update();
	void handleCollision(std::weak_ptr<GameObject>);
	Player *player;
};

class Player : public Character {
public:
	Player(PiruGameState*);
	void render(sf::RenderWindow *window);
	void update();
	void handleCollision(std::weak_ptr<GameObject>);
	
	int lastSpellUsed;
	bool casting;
	float gravity;
	float ground;
	std::weak_ptr<GameObject> onPlat;
};
