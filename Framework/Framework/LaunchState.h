#pragma once

#include <SFML\Graphics.hpp>

#include "State.h"
#include "Game.h"

//setting up the lua library (data scripting)
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include <LuaBridge/LuaBridge.h>

using namespace sf;

class LaunchState: public State
{
public:
	LaunchState(GameDataRef data); // what is in the brackets are all of the items that form the application
	~LaunchState();

	void Init();  //function used for initialising
	void Input();
	void Update(float delta);
	void Draw(float delta);

private:
	GameDataRef _data; //pointer to the actual GameDataRef
	Clock _clock; //to let you know for how long the application has been runnning for

	//creating the sprites
	Sprite _background;
	Sprite _text;
};

