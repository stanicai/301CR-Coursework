#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

#include "State.h"
#include "Game.h"
#include "Player.h"
#include "Weapon.h"
#include "Enemy.h"
#include "RandomWall.h"
#include "HorizontalWall.h"
#include "MyContactListener.h"
#include "FPS.h"
#include "Audio.h"

using namespace sf;

class GameLevel2 : public State
{
public:
	GameLevel2(GameDataRef data);

	void Init();
	void Input();
	void Update(float delta);
	void Draw(float delta);

	//initialising the scene objects
	Player _player;
	Enemy _enemy;
	RandomWall _wall;
	HorizontalWall _hoWall;
	FPS _fps;
	Audio _audio;

	vector <Enemy>::const_iterator iterEnemy; //the iterator that goes through the enemy array
	vector <Enemy> enemyArray;  //the array in which the enemyes will be stored

	//bools to limit the amount of walls and enemies spawning
	bool vertical = false;
	bool horizontal = false;
	bool enemyInitialise = false;

	MyContactListener myContactListenerInstance; //used when checking if there was a collision between the objects that have colliders from box2d
	Clock missleClock; //clock for the weapon delay
private:
	GameDataRef _data;

	Sprite _background;  //the background image
	Sprite _pauseButton; //the pause button image
};

