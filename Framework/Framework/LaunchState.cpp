#include "LaunchState.h"
#include "GameValues.h"
#include "MainMenuState.h"
#include "GameRules.h"

#include <sstream>
#include <iostream>



using namespace std;
using namespace sf;
using namespace luabridge;

LaunchState::LaunchState(GameDataRef data): _data(data)
{
}

LaunchState::~LaunchState()
{
}

string launchStateFilePath;
string launchStateBackground;
int launchStateTimeWait;

void LaunchState::Init()
{
	//setting up lua and the file it uses for data
	lua_State* F = luaL_newstate();
	luaL_dofile(F, "level.lua");
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);

	LuaRef l = getGlobal(F, "launch");
	LuaRef tit = l["launchStateFilePath"]; 
	LuaRef tim = l["launchStateTimeWait"];
	LuaRef lback = l["launchStateBackground"];

	launchStateFilePath = tit.cast<std::string>();
	launchStateTimeWait = tim.cast<int>();
	launchStateBackground = lback.cast<string>();

	//loading the textures
	this->_data->assets.LoadTexture("Launch Sate Background", LAUNCH_STATE_WINDOW_BACKGROUND_FILEPATH);
	this->_data->assets.LoadTexture("Launch Sate Text", LAUNCH_STATE_WINDOW_TEXT_FILEPATH);

	//assigning the textures
	_background.setTexture(this->_data->assets.getTexture("Launch Sate Background"));
	_text.setTexture(this->_data->assets.getTexture("Launch Sate Text"));

	//setting up the position of the image
	this->_text.setPosition((GAME_WINDOW_WIDTH / 2) - (this->_text.getGlobalBounds().width / 2), (GAME_WINDOW_HIGHT / 2) - (this->_text.getGlobalBounds().height / 2)*1.5);

}

void LaunchState::Input()
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

void LaunchState::Update(float delta)
{
	//after a certain amount of time has passed it will move to the game rules state
	if (this->_clock.getElapsedTime().asSeconds() > LAUNCH_STATE_TIME)
	{
		this->_data->machine.AddState(StateRef(new GameRules(_data)), true);
	}
}

void LaunchState::Draw(float delta)
{
	this->_data->window.clear(Color::Black);

	//drawing the images into the scene
	this->_data->window.draw(this->_background);
	this->_data->window.draw(this->_text);

	this->_data->window.display();
}
