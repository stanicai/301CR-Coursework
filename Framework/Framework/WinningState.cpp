#include <sstream>
#include <iostream>

#include "WinningState.h"
#include "GameValues.h"
#include "GameState.h"
#include "MainMenuState.h"

using namespace sf;
using namespace std;

WinningState::WinningState(GameDataRef data) :_data(data)
{
}

std::string winningBackground;
std::string winningImage;
std::string winningExit;

void WinningState::Init()
{
	//setting up lua and the file it uses for data
	lua_State* F = luaL_newstate();
	luaL_dofile(F, "level.lua");
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);

	LuaRef w = getGlobal(F, "winning");
	LuaRef wback = w["winningBackground"];
	LuaRef wImg = w["winningImage"];
	LuaRef wExit = w["winningExit"];

	winningBackground = wback.cast<std::string>();
	winningImage = wImg.cast<string>();
	winningExit = wExit.cast<string>();

	//loading the textures
	this->_data->assets.LoadTexture("Background", WINNING_WINDOW_BACKGROUND_FILEPATH);
	this->_data->assets.LoadTexture("Game_Won", GAME_WON);
	this->_data->assets.LoadTexture("Exit", WINNING_EXIT);

	//assigning the textures
	this->_backgroud.setTexture(this->_data->assets.getTexture("Background"));
	this->_won.setTexture(this->_data->assets.getTexture("Game_Won"));
	this->_exit.setTexture(this->_data->assets.getTexture("Exit"));

	//setting the position of the won and exit buttons
	this->_won.setPosition((GAME_WINDOW_WIDTH / 2) - (this->_won.getGlobalBounds().width / 2), (GAME_WINDOW_HIGHT / 2) - (this->_won.getGlobalBounds().height / 2)*2);
	this->_exit.setPosition((GAME_WINDOW_WIDTH / 2) - (this->_exit.getGlobalBounds().width / 2), _won.getPosition().y + _exit.getGlobalBounds().height * 2);

}

void WinningState::Input()
{
	Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (Event::Closed == event.type)
		{
			this->_data->window.close();
		}

		//if the the mouse left button is clicked on the exit sprite then the window is closed
		if (this->_data->input.isSpriteClicked(this->_exit, Mouse::Left, this->_data->window))
		{
			this->_data->window.close();
		}
	}
}

void WinningState::Update(float delta)
{
	//if the escape button is pressed then the window is closed
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		this->_data->window.close();
	}
}

void WinningState::Draw(float delta)
{
	this->_data->window.clear(Color::Black);

	//drawing the images into the scene 
	this->_data->window.draw(this->_backgroud);
	this->_data->window.draw(this->_won);
	this->_data->window.draw(this->_exit);

	this->_data->window.display();
}