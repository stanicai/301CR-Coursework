#include <sstream>
#include <iostream>

#include "Enemy.h"
#include "GameValues.h"
#include "Player.h"


Enemy::Enemy(GameDataRef data): _data(data)
{

}

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

//function that outputs a random number that takes a maximum value that it allowed to reach
int Enemy::randomMethod(int max)
{
	int randomNo = rand();
	float random = (randomNo%max) + 1;
	int myRandom = random;
	return myRandom;
}

void Enemy::Init()
{
	//setting up the sprite bounds, so the texture will be only in that rectangle 
	_sprite.setTextureRect(IntRect(0, 0, ENEMY_SPRITE_SIZE_WIDTH, ENEMY_SPRITE_SIZE_HIGHT));

	_playerBox.SetAsBox(_playerHalfWidth, _playerHalfWidth);

	_playerBD.type = b2_dynamicBody;  //setting the body as dynamic so it would know that it is going to move

	//this is the position in meters on the x and y axis
	_playerBD.position.Set(7.5f, -1.5f);

	//setting the fixture parameters based on which the object will know how to interact with the other ones in the scene 
	fixtureDef.shape = &_playerBox;
	fixtureDef.density = 0.3f;
	fixtureDef.friction = 0.3f;

	//setting up the graphic position based on the physics and half of its width; 
	//it is multiplied with the scaling factor so it would be converted back to the pixel size so its position would match the sfml requirements
	_playerGraphicsPosition.x = (_playerPhysicsPosition.x - _playerHalfWidth)*scalingFactor;
	_playerGraphicsPosition.y = (_playerPhysicsPosition.y + _playerHalfWidth)*scalingFactor*-1.0f;


	//setting the sprite position 
	_sprite.setPosition(_playerGraphicsPosition);
}

void Enemy::Update(float delta)
{
	world.Step(timeStep, velocityIterations, positionIterations);

	//setting the data to be recongnised the by the contact listener for when a collision happens to know exactly what types of collisions are occuring
	//and to have a response based on that
	_playerMove->SetUserData((void*)"enemy");

	_playerMove->SetLinearVelocity(b2Vec2(0.0f, 0.0f));  //setting the speed to 0 while it isn't moving


	//based on the direction the enemy will move with the linear velocity and the sprite will take the images for that particular direction
	if (direction == 1)
	{
		_playerMove->SetLinearVelocity(b2Vec2(0.0f, ENEMY_MOVEMENT_SPEED));
		_sprite.setTextureRect(IntRect(spriteCounter*ENEMY_SPRITE_SIZE_WIDTH, ENEMY_SPRITE_SIZE_HIGHT * 8, ENEMY_SPRITE_SIZE_WIDTH, ENEMY_SPRITE_SIZE_HIGHT));
	}
	else if (direction == 2)
	{
		_playerMove->SetLinearVelocity(b2Vec2(0.0f, -ENEMY_MOVEMENT_SPEED));
		_sprite.setTextureRect(IntRect(spriteCounter*ENEMY_SPRITE_SIZE_WIDTH, ENEMY_SPRITE_SIZE_HIGHT * 10, ENEMY_SPRITE_SIZE_WIDTH, ENEMY_SPRITE_SIZE_HIGHT));
	}
	else if (direction == 3)
	{
		_playerMove->SetLinearVelocity(b2Vec2(-ENEMY_MOVEMENT_SPEED, 0.0f));
		_sprite.setTextureRect(IntRect(spriteCounter*ENEMY_SPRITE_SIZE_WIDTH, ENEMY_SPRITE_SIZE_HIGHT * 9, ENEMY_SPRITE_SIZE_WIDTH, ENEMY_SPRITE_SIZE_HIGHT));
	}
	else if (direction == 4)
	{
		_playerMove->SetLinearVelocity(b2Vec2(ENEMY_MOVEMENT_SPEED, 0.0f));
		_sprite.setTextureRect(IntRect(spriteCounter*ENEMY_SPRITE_SIZE_WIDTH, ENEMY_SPRITE_SIZE_HIGHT * 11, ENEMY_SPRITE_SIZE_WIDTH, ENEMY_SPRITE_SIZE_HIGHT));
	}
	else
	{
		//no movement
	}

	spriteCounter++;
	if (spriteCounter == ENEMY_SPRITE_COUNTER_CYCLE)
	{
		spriteCounter = 0;
	}

	counter++;
	if (counter >= ENEMY_MOVEMENT_AMOUNT)
	{
		direction = randomMethod(10);//this will give a random position for the enemy, it has a higher chance of sitting still, but if it doesn't it will move in one of the directions
		counter = 0;
	}

	_playerPhysicsPosition = _playerMove->GetPosition(); //the physics position is based on the movement position

	_playerGraphicsPosition.x = (_playerPhysicsPosition.x - _playerHalfWidth)*scalingFactor;
	_playerGraphicsPosition.y = (_playerPhysicsPosition.y + _playerHalfWidth)*scalingFactor*-1.0f;

	_sprite.setPosition(_playerGraphicsPosition);
}
