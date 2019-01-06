#include <sstream>
#include <iostream>

#include "GameRules.h"
#include "GameValues.h"
#include "GameState.h"
#include "MainMenuState.h"

using namespace sf;
using namespace std;

GameRules::GameRules(GameDataRef data) :_data(data)
{
}

std::string rulesBackground;
std::string rulesImage;

void GameRules::Init()
{
	//setting up lua and the file it uses for data
	lua_State* F = luaL_newstate();
	luaL_dofile(F, "level.lua");
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);

	LuaRef r = getGlobal(F, "gameRules");
	LuaRef rback = r["rulesBackground"];
	LuaRef rImg = r["rulesImage"];

	rulesBackground = rback.cast<std::string>();
	rulesImage = rImg.cast<string>();

	//loading the textures
	this->_data->assets.LoadTexture("Background",GAME_RULES_WINDOW_BACKGROUND_FILEPATH);
	this->_data->assets.LoadTexture("Game_Rules", GAME_RULES);

	//assigning the textures
	this->_backgroud.setTexture(this->_data->assets.getTexture("Background"));
	this->_gameRules.setTexture(this->_data->assets.getTexture("Game_Rules"));
}

void GameRules::Input()
{
	Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (Event::Closed == event.type)
		{
			this->_data->window.close();
		}
	}
}

void GameRules::Update(float delta)
{
	//if the enter button is pressed then it moves to the menu state
	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);

	}

	//if the escape button is pressed then the window is closed
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		this->_data->window.close();
	}
}

void GameRules::Draw(float delta)
{
	this->_data->window.clear(Color::Black);

	//drawing the images into the scene
	this->_data->window.draw(this->_backgroud);
	this->_data->window.draw(this->_gameRules);

	this->_data->window.display();
}
