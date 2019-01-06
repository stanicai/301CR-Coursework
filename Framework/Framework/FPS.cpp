#include "FPS.h"
#include <iostream>
using namespace std;

FPS::FPS(GameDataRef data): _data(data)
{

}

FPS::FPS()
{
}


FPS::~FPS()
{
}

void FPS::Init()
{
	//setting up the text
	_text.setString("FPS		" + to_string((int)fps));
	_text.setCharacterSize(24);
	_text.setFillColor(Color::White);
}

void FPS::Update(float delta)
{
	//getting the elapsed time for the delay
	Time elapsed = delay.getElapsedTime();

	//checking if the time has passed so the text can be updated
	if (elapsed.asSeconds() >= 0.1)
	{
		delay.restart();
		_text.setString("FPS		" + to_string((int)fps));
	}

	float timeNow = fpsClock.getElapsedTime().asSeconds();	//getting the elapsed time for the fps
	fps = 1.0f / (timeNow - fpscheck);
	fpscheck = timeNow;
}
