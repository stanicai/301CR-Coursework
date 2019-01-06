#include "Game.h"
#include "LaunchState.h"

using namespace sf;

Game::Game(int ScreenWidth, int ScreenHeight, string ApplicationName)
{
	//the last parameter just means that there will be a close and title bar parameter
	_data->window.create(VideoMode(ScreenWidth, ScreenHeight), ApplicationName, Style::Close | Style::Titlebar);
	_data->machine.AddState(StateRef(new LaunchState(this->_data)));

	this->Run();
}

void Game::Run()
{
	float newTime, frameTime, interpolation;

	float currentTime = this->_clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (this->_data->window.isOpen())
	{
		this->_data->machine.ProcessStateChanges();

		this->_data->window.setFramerateLimit(60);  //capping the frame rate at 60 

		newTime = this->_clock.getElapsedTime().asSeconds();

		frameTime = newTime - currentTime; //there are never the same (it might be a frame rate that differs) and there needs to be a frame time in place to handle any diffrences in frame times 
		
		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime; //a total of all the frame times

		while (accumulator >= delta)
		{
			this->_data->machine.getActiveState()->Input();
			this->_data->machine.getActiveState()->Update(delta);

			accumulator -= delta;
		}

		interpolation = accumulator / delta;
		this->_data->machine.getActiveState()->Draw(interpolation);
	}
}
