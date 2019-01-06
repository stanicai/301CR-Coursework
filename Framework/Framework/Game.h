#pragma once

#include <memory>
#include <string>

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

using namespace std;
using namespace sf;

static float scalingFactor = 200.0f;  //the scaling factor based on which the conversiton between pixels(used by sfml) and meteres(used by box2d) is made
static b2Vec2 gravity(0.0f, 0.0f);  //setting up the gravity values
static b2World world(gravity);		//setting up the gravity for the game world

struct GameData
{
	StateMachine machine;
	RenderWindow window;
	AssetManager assets;
	InputManager input;
};

typedef shared_ptr<GameData> GameDataRef;

class Game
{
public:
	Game(int ScreenWidth, int ScreenHeight, string ApplicationName);
private:
	const float delta = 1.0f / 60.0f; //the frame rate or how many times you want to update per second 
	Clock _clock; // used for handling the frame rate

	GameDataRef _data = make_shared<GameData>(); //what will be used to access the different states during the game

	void Run();
};

