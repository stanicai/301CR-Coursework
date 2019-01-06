#include <sstream>
#include <iostream>

#include "Player.h"
#include "Player2.h"
#include "GameValues.h"
#include "Game.h"
#include "Weapon.h"

Player2::Player2(GameDataRef data) : _data(data)
{
}

Player2::Player2()
{
}


Player2::~Player2()
{
}

void Player2::Init()
{
	//setting up the sprite bounds, so the texture will be only in that rectangle 
	_sprite.setTextureRect(IntRect(0, 0, SPRITE_SIZE_WIDTH, SPRITE_SIZE_HIGHT));

	_playerBox.SetAsBox(_playerHalfWidth, _playerHalfWidth);

	_playerBD.type = b2_dynamicBody;  //setting the body as dynamic so it would know that it is going to move

	//this is the player's position in meters on the x and y axis
	_playerBD.position.Set(3.5f, -0.5f);

	//setting the fixture parameters based on which the object will know how to interact with the other ones in the scene 
	fixtureDef.shape = &_playerBox;
	fixtureDef.density = 0.3f;
	fixtureDef.friction = 0.3f;

	_playerPhysicsPosition.x = 3.5f;
	_playerPhysicsPosition.y = -0.5f;

	//setting up the graphic position based on the physics and half of its width; 
	//it is multiplied with the scaling factor so it would be converted back to the pixel size so its position would match the sfml requirements
	_playerGraphicsPosition.x = (_playerPhysicsPosition.x - _playerHalfWidth)*scalingFactor;
	_playerGraphicsPosition.y = (_playerPhysicsPosition.y + _playerHalfWidth)*scalingFactor*-1.0f;

	_sprite.setPosition(_playerGraphicsPosition);

	//setting up the text that displays the player hp
	_text.setCharacterSize(24);
	_text.setFillColor(Color::White);
}

void Player2::Update(float delta)
{
	world.Step(timeStep, velocityIterations, positionIterations);

	//setting the data to be recongnised the by the contact listener for when a collision happens to know exactly what types of collisions are occuring
	//and to have a response based on that
	_playerMove->SetUserData((void*)"player");

	//based on the direction the player sprite will take the images for that particular direction
	if (direction == 1)
	{
		_sprite.setTextureRect(IntRect(spriteCounter*ENEMY_SPRITE_SIZE_WIDTH, ENEMY_SPRITE_SIZE_HIGHT * 8, ENEMY_SPRITE_SIZE_WIDTH, ENEMY_SPRITE_SIZE_HIGHT));
	}
	else if (direction == 2)
	{
		_sprite.setTextureRect(IntRect(spriteCounter*ENEMY_SPRITE_SIZE_WIDTH, ENEMY_SPRITE_SIZE_HIGHT * 10, ENEMY_SPRITE_SIZE_WIDTH, ENEMY_SPRITE_SIZE_HIGHT));
	}
	else if (direction == 3)
	{
		_sprite.setTextureRect(IntRect(spriteCounter*ENEMY_SPRITE_SIZE_WIDTH, ENEMY_SPRITE_SIZE_HIGHT * 9, ENEMY_SPRITE_SIZE_WIDTH, ENEMY_SPRITE_SIZE_HIGHT));
	}
	else if (direction == 4)
	{
		_sprite.setTextureRect(IntRect(spriteCounter*ENEMY_SPRITE_SIZE_WIDTH, ENEMY_SPRITE_SIZE_HIGHT * 11, ENEMY_SPRITE_SIZE_WIDTH, ENEMY_SPRITE_SIZE_HIGHT));
	}
	else
	{
		//no movement
	}

	spriteCounter++;
	if (spriteCounter == SPRITE_COUNTER_CYCLE)
	{
		spriteCounter = 0;
	}

	_playerPhysicsPosition = _playerMove->GetPosition();  //the physics position is based on the movement position
	_playerGraphicsPosition.x = (_playerPhysicsPosition.x - _playerHalfWidth)*scalingFactor;
	_playerGraphicsPosition.y = (_playerPhysicsPosition.y + _playerHalfWidth)*scalingFactor*-1.0f;

	_sprite.setPosition(_playerGraphicsPosition);
}