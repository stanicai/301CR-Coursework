#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "Entity.h"
#include "State.h"
#include "Game.h"
#include "GameValues.h"

using namespace sf;

class Weapon : public Entity
{
public:
	Weapon(GameDataRef data);
	Weapon();
	~Weapon();

	void Init();   //function used for initialising
	void Update(float delta);

	//setting up the missle shape
	RectangleShape missle;
	RectangleShape missleDirection;

	int direction = 1;  // setting up the direction for the bullet movement

	int bulletsUsed = 0;  //the counter for the bullets used
	bool deleteBullets = false;  //setting up the bool that check if there should be any bullets deleted
	int points = 0;

	Clock clockWeapon;
	Time elapsed;
	Text _textPoints;
private:
	GameDataRef _data;
};