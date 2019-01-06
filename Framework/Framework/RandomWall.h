#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "Entity.h"
#include "State.h"
#include "Game.h"
#include "GameValues.h"

using namespace sf;

class RandomWall: public Entity
{
public:
	RandomWall(GameDataRef data);
	RandomWall();
	~RandomWall();

	//function that outputs a random number that takes a maximum value that it allowed to reach
	int randomMethod(int max);

	void Init();  //function used for initialising
	void Update(float delta);

	// assigning the half width and height of the wall
	float groundHalfWidth = 1.0f;
	float groundHalfHeight = 0.25f;

	vector <RandomWall>::const_iterator iterWall;  //the iterator that goes through the wall array
	vector <RandomWall> wallArray;  //the array in which the walls will be stored

	RectangleShape rect;  //setting up the shape of the wall
	b2Body* groundBody;  //the body created with box2d 
	b2PolygonShape groundBox;  //creating the virtual shape which is used by the physics system to check the collisions
	b2BodyDef groundBodyDef;  //this is the body definition with which you set its initial position and the to which you can assign the type of body
	b2Vec2 groundPhysicsPosition;  //the vector which takes the physics postion (where the collider is)
	Vector2f groundGraphicsPosition;  //the vector which takes the position where the texture should be drawn
private:
	GameDataRef _data;
};

