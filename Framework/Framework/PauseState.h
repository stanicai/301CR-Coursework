#pragma once

#include <SFML\Graphics.hpp>
#include "State.h"
#include "Game.h"

using namespace sf;

class PauseState : public State
{
public:
	PauseState(GameDataRef data);

	void Init();  //function used for initialising
	void Input();
	void Update(float delta);
	void Draw(float delta);
private:
	GameDataRef _data;

	//creating the sprites
	Sprite _backgroud;
	Sprite _pauseTitle;
	Sprite _resume;
	Sprite _exit;
};



