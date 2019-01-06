#include <sstream>
#include <iostream>

#include "PauseState.h"
#include "GameValues.h"
#include "GameState.h"

using namespace sf;
using namespace std;


PauseState::PauseState(GameDataRef data) :_data(data)
{
}

std::string pauseBackground;
std::string pauseImage;
std::string pauseResume;
std::string pauseExit;

void PauseState::Init()
{
	//setting up lua and the file it uses for data
	lua_State* F = luaL_newstate();
	luaL_dofile(F, "level.lua");
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);

	LuaRef p = getGlobal(F, "pause");
	LuaRef pback = p["pauseBackground"];
	LuaRef pImg = p["pauseImage"];
	LuaRef pResume = p["pauseResume"];
	LuaRef pExit = p["pauseExit"];

	pauseBackground = pback.cast<std::string>();
	pauseImage = pImg.cast<string>();
	pauseResume = pResume.cast<string>();
	pauseExit = pExit.cast<string>();

	//loading the textures
	this->_data->assets.LoadTexture("Background", PAUSE_WINDOW_BACKGROUND_FILEPATH);
	this->_data->assets.LoadTexture("Pause_Title", PAUSE_TEXTURE);
	this->_data->assets.LoadTexture("Resume", PAUSE_RESUME);
	this->_data->assets.LoadTexture("Exit", PAUSE_EXIT);

	//assigning the textures
	this->_backgroud.setTexture(this->_data->assets.getTexture("Background"));
	this->_pauseTitle.setTexture(this->_data->assets.getTexture("Pause_Title"));
	this->_resume.setTexture(this->_data->assets.getTexture("Resume"));
	this->_exit.setTexture(this->_data->assets.getTexture("Exit"));

	//setting the button positions
	this->_resume.setPosition((GAME_WINDOW_WIDTH / 2) - (this->_resume.getGlobalBounds().width / 2), (GAME_WINDOW_HIGHT / 2) - (this->_resume.getGlobalBounds().height / 2)*3);
	this->_exit.setPosition((GAME_WINDOW_WIDTH / 2) - (this->_exit.getGlobalBounds().width / 2), _resume.getPosition().y + _exit.getGlobalBounds().height*2);
	this->_pauseTitle.setPosition((GAME_WINDOW_WIDTH / 2) - (this->_pauseTitle.getGlobalBounds().width / 2), this->_pauseTitle.getGlobalBounds().height*0.5);

}

void PauseState::Input()
{
	Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (Event::Closed == event.type)
		{
			this->_data->window.close();
		}
		//if the resume button is clicked this state is being removed
		if (this->_data->input.isSpriteClicked(this->_resume, Mouse::Left, this->_data->window))
		{
			this->_data->machine.RemoveState();
		}
		//if the exit button is clicked the window is closed
		if (this->_data->input.isSpriteClicked(this->_exit, Mouse::Left, this->_data->window))
		{
			this->_data->window.close();
		}
	}
}

void PauseState::Update(float delta)
{
	//if the escape button is pressed then the window is closed
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		this->_data->window.close();
	}
}

void PauseState::Draw(float delta)
{
	this->_data->window.clear(Color::Black);

	//drawing the images into the scene
	this->_data->window.draw(this->_backgroud);
	this->_data->window.draw(this->_pauseTitle);
	this->_data->window.draw(this->_resume);
	this->_data->window.draw(this->_exit);

	this->_data->window.display();
}
