#pragma once

#include <SFML\Graphics.hpp>
#include "State.h"
#include "Game.h"

using namespace sf;

class GameRules : public State
{
public:
	GameRules(GameDataRef data);

	void Init();   //function used for initialising
	void Input();
	void Update(float delta);
	void Draw(float delta);
private:
	GameDataRef _data;

	//creating the sprites for the background, and game rules
	Sprite _backgroud;
	Sprite _gameRules;
};