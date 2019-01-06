#pragma once

//setting up the sfml library (graphics)
#include <SFML\Graphics.hpp>

//setting up the box2d library (physics)
#include <Box2D\Box2D.h>
//setting up the class headers 
#include "State.h"
#include "Game.h"
#include "Player.h"
#include "Weapon.h"
#include "Enemy.h"
#include "RandomWall.h"
#include "HorizontalWall.h"
#include "MyContactListener.h"
#include "FPS.h"
#include "Player2.h"
#include "Audio.h"

//setting up the lua library (data scripting)
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include <LuaBridge/LuaBridge.h>

//setting up the enet library (network)
#include <enet/enet.h>

using namespace luabridge;
using namespace sf;



//used with the network to get the values 
struct Vector2Test {
	float x;
	float y;
	float direction;
	bool weapon;
};

class GameState: public State
{
public:
	GameState(GameDataRef data);

	void Init();  //function used for initialising
	void Input();
	void Update(float delta);
	void Draw(float delta);

	//initialising the scene objects
	Player _player;
	Player2 _player2;/////////////////////////
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

	//////////////
	void enetFunction();
private:
	GameDataRef _data;

	Sprite _background;  //the background image
	Sprite _pauseButton; //the pause button image
};

