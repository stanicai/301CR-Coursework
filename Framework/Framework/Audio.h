#pragma once

#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "State.h"
#include "Game.h"
#include "GameValues.h"

//setting up the fmod library (audio)
#include <fmod_studio.hpp>
#include <fmod.hpp>
#include <fmod.h>

//setting up the lua library (data scripting)
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include <LuaBridge/LuaBridge.h>

using namespace luabridge;

class Audio: public Entity
{
public:
	Audio(GameDataRef data);
	Audio();
	~Audio();

	void Init();   //function used for initialising
	void Update(float delta);

	FMOD::System *system = NULL;  //fmod sound system - used to play the sounds
	FMOD::Sound *sound = NULL;	  //this sound is the one for the background
	FMOD::Channel *channel = NULL;;
	FMOD_RESULT result;

	//sound1 will take the shooting sound
	FMOD::Sound *sound1 = NULL;
	FMOD::Channel *channel1 = NULL;;
	FMOD_RESULT result1;

	//sound2 will take the footstep sound
	FMOD::Sound *sound2 = NULL;
	FMOD::Channel *channel2 = NULL;;
	FMOD_RESULT result2;
private:
	GameDataRef _data;
};

