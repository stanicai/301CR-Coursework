#pragma once

#include <SFML\Graphics.hpp>
#include "State.h"
#include "Game.h"

using namespace sf;

class MainMenuState: public State
{
public:
	MainMenuState(GameDataRef data);

	void Init(); //function used for initialising
	void Input();
	void Update(float delta);
	void Draw(float delta);
private:
	GameDataRef _data;

	//creating the sprites
	Sprite _backgroud;
	Sprite _play;
	Sprite _title;
	Sprite _exit;
};

