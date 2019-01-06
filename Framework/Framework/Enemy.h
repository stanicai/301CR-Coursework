#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "Entity.h"
#include "State.h"
#include "Game.h"

using namespace sf;

//the enemy class is very similar to the player class, I've used this is why some variables are identical
class Enemy:public Entity
{
public:
	Enemy(GameDataRef data);
	Enemy();
	~Enemy();

	//function that outputs a random number that takes a maximum value that it allowed to reach
	int randomMethod(int max);

	void Init();  //function used for initialising
	void Update(float delta);

	b2PolygonShape _playerBox;  //creating the virtual shape which is used by the physics system to check the collisions
	b2BodyDef _playerBD;  //this is the body definition with which you set its initial position and the to which you can assign the type of body
	b2FixtureDef fixtureDef; //the fixture created for the collider

	b2Body* _playerMove;  //the body created with box2d 
	Vector2f _playerGraphicsPosition;  //the vector which takes the position where the texture should be drawn
	b2Vec2 _playerPhysicsPosition;  //the vector which takes the physics postion (where the collider is)
	float _playerHalfWidth = 0.12f; //used for the collider

	int direction = 1;  //the direction in which it is facing, based on the movement
	int counter =0;  //the counter for the period of time a direction is being used before being changed
private:
	GameDataRef _data;
	int spriteCounter = 0;  //the counter that goes through the sprite animation so when it moves it looks like a real walk cycle
};

