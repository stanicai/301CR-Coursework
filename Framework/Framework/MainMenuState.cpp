#include <sstream>
#include <iostream>

#include "MainMenuState.h"
#include "GameValues.h"
#include "GameState.h"

using namespace sf;
using namespace std;

MainMenuState::MainMenuState(GameDataRef data): _data(data)
{

}

std::string menuBackground;
std::string menuTitleImage;
std::string menuPlayButton;
std::string menuExit;

void MainMenuState::Init()
{
	//setting up lua and the file it uses for data
	lua_State* F = luaL_newstate();
	luaL_dofile(F, "level.lua");
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);

	LuaRef m = getGlobal(F, "menu");
	LuaRef mback = m["menuBackground"];
	LuaRef ply = m["menuPlayButton"];
	LuaRef mtit = m["menuTitleImage"];
	LuaRef mExit = m["menuExit"];

	menuBackground = mback.cast<std::string>();
	menuPlayButton = ply.cast<string>();
	menuTitleImage = mtit.cast<string>();
	menuExit = mExit.cast<string>();

	//loading the textures
	this->_data->assets.LoadTexture("Background", MAIN_MENU_WINDOW_BACKGROUND_FILEPATH);
	this->_data->assets.LoadTexture("Play", MAIN_MENU_PLAY);
	this->_data->assets.LoadTexture("Title", MAIN_MENU_TITLE);
	this->_data->assets.LoadTexture("Exit", MAIN_MENU_EXIT);
	
	//assigning the textures
	this->_backgroud.setTexture(this->_data->assets.getTexture("Background"));
	this->_play.setTexture(this->_data->assets.getTexture("Play"));
	this->_title.setTexture(this->_data->assets.getTexture("Title"));
	this->_exit.setTexture(this->_data->assets.getTexture("Exit"));

	//setting up the position of the play button
	this->_play.setPosition((GAME_WINDOW_WIDTH / 2) - (this->_play.getGlobalBounds().width / 2), (GAME_WINDOW_HIGHT / 2) - (this->_play.getGlobalBounds().height / 2)*2.5);
	
	//scaling down the exit button and then setting up its position
	this->_exit.scale(0.75, 0.75);
	this->_exit.setPosition((GAME_WINDOW_WIDTH / 2) - (this->_exit.getGlobalBounds().width / 2), _play.getPosition().y + _exit.getGlobalBounds().height * 2);

	this->_title.setPosition((GAME_WINDOW_WIDTH / 2) - (this->_title.getGlobalBounds().width / 2), this->_title.getGlobalBounds().height*0.5);

}

void MainMenuState::Input()
{
	Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (Event::Closed == event.type)
		{
			this->_data->window.close();
		}

		//if the play button is clicked then the game state starts
		if (this->_data->input.isSpriteClicked(this->_play, Mouse::Left, this->_data->window))
		{
			this->_data->machine.AddState(StateRef(new GameState(_data)), true);
		}
		//if the exit button is clicked the the window is closed
		if (this->_data->input.isSpriteClicked(this->_exit, Mouse::Left, this->_data->window))
		{
			this->_data->window.close();
		}
	}
}

void MainMenuState::Update(float delta)
{
	//if the escape button is pressed then the window is closed
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		this->_data->window.close();
	}
}

void MainMenuState::Draw(float delta)
{
	this->_data->window.clear(Color::Black);

	//drawing the images into the scene
	this->_data->window.draw(this->_backgroud);
	this->_data->window.draw(this->_play);
	this->_data->window.draw(this->_title);
	this->_data->window.draw(this->_exit);

	this->_data->window.display();
}
