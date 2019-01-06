#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
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
using namespace luabridge;

//this class is the one from which most of them inherit, so the similar values wouldn't have to be defined multiple times
class Entity
{
public:
	float _playerSpeed;
	int _playerHP;

	Sprite _sprite;
	Text _text;

	int randomMethod(int max);
};