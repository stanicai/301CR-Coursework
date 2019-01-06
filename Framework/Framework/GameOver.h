#pragma once

#include <SFML\Graphics.hpp>
#include "State.h"
#include "Game.h"

using namespace sf;

class GameOver: public State
{
public:
	GameOver(GameDataRef data);

	void Init();  //function used for initialising
	void Input();
	void Update(float delta);
	void Draw(float delta);
private:
	GameDataRef _data;

	//creating the sprites for the background, game over and exit
	Sprite _backgroud;
	Sprite _gameOver;
	Sprite _exit;
};

