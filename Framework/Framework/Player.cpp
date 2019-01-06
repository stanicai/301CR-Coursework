#include <sstream>
#include <iostream>

#include "Player.h"
#include "GameValues.h"
#include "Game.h"
#include "Weapon.h"

int condition = 0;

Player::Player(GameDataRef data): _data(data)
{

}

Player::Player()
{
}


Player::~Player()
{
}

void Player::Init()
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

	//setting up the graphic position based on the physics and half of its width; 
	//it is multiplied with the scaling factor so it would be converted back to the pixel size so its position would match the sfml requirements
	_playerGraphicsPosition.x = (_playerPhysicsPosition.x - _playerHalfWidth)*scalingFactor;
	_playerGraphicsPosition.y = (_playerPhysicsPosition.y + _playerHalfWidth)*scalingFactor*-1.0f;

	_sprite.setPosition(_playerGraphicsPosition);

	//setting up the text that displays the player hp
	_text.setString("The Player HP		" + to_string(health) + "	OF	" + to_string(PLAYER_ALL_HP));
	_text.setCharacterSize(24);
	_text.setFillColor(Color::White);
}

void Player::Update(float delta)
{
	world.Step(timeStep, velocityIterations, positionIterations);
	_playerMove->SetLinearVelocity(b2Vec2(0.0f, 0.0f)); //setting the speed to 0 while it isn't moving

	//updating the text 
	_text.setString("THE	PLAYER	HP		" + to_string(health) + "	OF	" + to_string(PLAYER_ALL_HP));

	//setting the data to be recongnised the by the contact listener for when a collision happens to know exactly what types of collisions are occuring
	//and to have a response based on that
	_playerMove->SetUserData((void*)"player");


	//based on the key pressed the player will move with the linear velocity and the sprite will take the images for that particular direction
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		_playerMove->SetLinearVelocity(b2Vec2(0.0f, PLAYER_SPEED));
		_sprite.setTextureRect(IntRect(spriteCounter*SPRITE_SIZE_WIDTH, SPRITE_SIZE_HIGHT * 8, SPRITE_SIZE_WIDTH, SPRITE_SIZE_HIGHT));
		direction = 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		_playerMove->SetLinearVelocity(b2Vec2(0.0f, -PLAYER_SPEED));
		_sprite.setTextureRect(IntRect(spriteCounter*SPRITE_SIZE_WIDTH, SPRITE_SIZE_HIGHT * 10, SPRITE_SIZE_WIDTH, SPRITE_SIZE_HIGHT));
		direction = 2;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		_playerMove->SetLinearVelocity(b2Vec2(-PLAYER_SPEED, 0.0f));
		_sprite.setTextureRect(IntRect(spriteCounter*SPRITE_SIZE_WIDTH, SPRITE_SIZE_HIGHT * 9, SPRITE_SIZE_WIDTH, SPRITE_SIZE_HIGHT));
		direction = 3;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		_playerMove->SetLinearVelocity(b2Vec2(PLAYER_SPEED, 0.0f));
		_sprite.setTextureRect(IntRect(spriteCounter*SPRITE_SIZE_WIDTH, SPRITE_SIZE_HIGHT * 11, SPRITE_SIZE_WIDTH, SPRITE_SIZE_HIGHT));
		direction = 4;
	}

	spriteCounter++;
	if (spriteCounter == SPRITE_COUNTER_CYCLE)
	{
		spriteCounter = 0;
	}

	_playerPhysicsPosition = _playerMove->GetPosition(); //the physics position is based on the movement position
	_playerGraphicsPosition.x = (_playerPhysicsPosition.x - _playerHalfWidth)*scalingFactor;
	_playerGraphicsPosition.y = (_playerPhysicsPosition.y + _playerHalfWidth)*scalingFactor*-1.0f;

	_sprite.setPosition(_playerGraphicsPosition);
}