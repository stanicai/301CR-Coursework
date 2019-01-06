#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "Entity.h"
#include "State.h"
#include "Game.h"
#include "Weapon.h"
#include "GameValues.h"

using namespace sf;

class Player2 : public Entity
{
public:
	Player2(GameDataRef data);
	Player2();
	~Player2();

	void Init();  //function used for initialising

	void Update(float delta);

	b2PolygonShape _playerBox;  //creating the virtual shape which is used by the physics system to check the collisions
	b2BodyDef _playerBD;  //this is the body definition with which you set its initial position and the to which you can assign the type of body
	b2FixtureDef fixtureDef;  //the fixture created for the collider

	b2Body* _playerMove;  //the body created with box2d 
	Vector2f _playerGraphicsPosition;  //the vector which takes the position where the texture should be drawn
	b2Vec2 _playerPhysicsPosition;  //the vector which takes the physics postion (where the collider is)
	float _playerHalfWidth = 0.16f; //used for the collider

	Weapon _weapon;  //creating the weapon instance

	vector <Weapon>::const_iterator iter;  //the iterator that goes through the weapon array
	vector <Weapon> weaponArray;  //the array in which the weapons will be stored
	int direction = 1;  //the direction in which it is facing, based on the movement

	int health = PLAYER_ALL_HP;  //the player health
private:
	GameDataRef _data;
	int spriteCounter = 0;  //the counter that goes through the sprite animation so when it moves it looks like a real walk cycle

};


