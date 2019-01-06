#include <sstream>
#include <iostream>

#include "GameOver.h"
#include "GameValues.h"
#include "GameState.h"
#include "MainMenuState.h"

using namespace sf;
using namespace std;

GameOver::GameOver(GameDataRef data):_data(data)
{

}

std::string gameOverBackground;
std::string gameOverImage;
std::string gameOverExit;

void GameOver::Init()
{
	//setting up lua and the file it uses for data
	lua_State* F = luaL_newstate();
	luaL_dofile(F, "level.lua");
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);

	LuaRef o = getGlobal(F, "gameOver");
	LuaRef oback = o["gameOverBackground"];
	LuaRef oImg = o["gameOverImage"];
	LuaRef oExit = o["gameOverExit"];

	gameOverBackground = oback.cast<std::string>();
	gameOverImage = oImg.cast<string>();
	gameOverExit = oExit.cast<string>();

	//loading the textures
	this->_data->assets.LoadTexture("Background", GAME_OVER_WINDOW_BACKGROUND_FILEPATH);
	this->_data->assets.LoadTexture("Game_Over", GAME_OVER_MAIN_TEXTURE);
	this->_data->assets.LoadTexture("Exit", GAME_OVER_EXIT);

	//assigning the textures
	this->_backgroud.setTexture(this->_data->assets.getTexture("Background"));
	this->_gameOver.setTexture(this->_data->assets.getTexture("Game_Over"));
	this->_exit.setTexture(this->_data->assets.getTexture("Exit"));

	//setting the position of the exit button
	this->_exit.setPosition((GAME_WINDOW_WIDTH / 2) - (this->_exit.getGlobalBounds().width / 2), (GAME_WINDOW_HIGHT / 2) - (this->_exit.getGlobalBounds().height / 2));

	// setting the postion of the game over sprite
	this->_gameOver.setPosition((GAME_WINDOW_WIDTH / 2) - (this->_gameOver.getGlobalBounds().width / 2), this->_gameOver.getGlobalBounds().height*0.5);
}

void GameOver::Input()
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

void GameOver::Update(float delta)
{
	//if the escape button is pressed then the window is closed
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		this->_data->window.close();
	}
}

void GameOver::Draw(float delta)
{
	this->_data->window.clear(Color::Black);

	//drawing the images into the scene 
	this->_data->window.draw(this->_backgroud);
	this->_data->window.draw(this->_gameOver);
	this->_data->window.draw(this->_exit);

	this->_data->window.display();
}
