#pragma once

#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "State.h"
#include "Game.h"
#include "GameValues.h"

//a class that deals with the fps, used for measure them and display them 
class FPS:public Entity
{
public:
	FPS(GameDataRef data);
	FPS();
	~FPS();

	void Init();   //function used for initialising
	void Update(float delta);

	Clock fpsClock;  //the clock that is used for the elapsed time while measuring the fps
	Clock delay;    //the clock used for the text dealy so it would be readable, otherwise you wouldn't be able to tell cause they would change very fast
	float fpscheck = 0;
	float fps;
private:
	GameDataRef _data;
};

