#include "Weapon.h"
#include "GameValues.h"
#include "Player.h"
#include "GameState.h"

Weapon::Weapon(GameDataRef data): _data(data)
{

}

Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

void Weapon::Init()
{
	//initialising the missle by setting its size and posiiton
	missle.setSize(Vector2f(10, 10));
	missle.setPosition(0, 0);
	missle.setFillColor(Color::White);
	
	//setting up the text for the bullets
	_text.setCharacterSize(24);
	_text.setFillColor(Color::White);

	//setting up the text for the points
	_textPoints.setCharacterSize(24);
	_textPoints.setFillColor(Color::White);
}

void Weapon::Update(float delta)
{ 
	//based on the direction it gets from the player, the bullets move
	if (direction == 1)
	{
		missle.move(0, -WEAPON_MOVEMENT_SPEED);
	}
	if (direction == 2)
	{
		missle.move(0,WEAPON_MOVEMENT_SPEED);
	}
	if (direction == 3)
	{
		missle.move(-WEAPON_MOVEMENT_SPEED,0);
	}
	if (direction == 4)
	{
		missle.move(WEAPON_MOVEMENT_SPEED, 0);
	}

	//the elapsed time
	elapsed = clockWeapon.getElapsedTime();

	//if a certain amount of time has passed the bullets should be deleted
	if (elapsed.asSeconds() >= 1.5)
	{
		clockWeapon.restart();
		deleteBullets = true;
	}
	else
	{
		deleteBullets = false;
	}
}
