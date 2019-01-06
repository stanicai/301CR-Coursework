#include "Audio.h"



Audio::Audio(GameDataRef data): _data(data)
{

}

Audio::Audio()
{
}

Audio::~Audio()
{
}

const char* footstepSound;
const char* backgroundSound;
const char* weaponSound;

void Audio::Init()
{
	//setting up lua and the file it uses for data
	lua_State* F = luaL_newstate();
	luaL_dofile(F, "level.lua");
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);

	LuaRef s = getGlobal(F, "sound");
	LuaRef sfootstep = s["footstepSound"];
	LuaRef sbackground = s["backgroundSound"];
	LuaRef sweapon = s["weaponSound"];

	footstepSound = sfootstep.cast<const char* >();
	backgroundSound = sbackground.cast<const char* >();
	weaponSound = sweapon.cast<const char* >();

	//initialising the fmod sounds by creating them as well as the system
	result = FMOD::System_Create(&system);
	system->init(10, FMOD_INIT_NORMAL, 0);
	system->createSound(BACKGROUND_SOUND, FMOD_LOOP_NORMAL, NULL, &sound);
	system->createSound(WEAPON_SOUND, FMOD_DEFAULT, NULL, &sound1);
	system->createSound(FOOTSTEP_SOUND, FMOD_DEFAULT, NULL, &sound2);

	result = system->playSound(sound, NULL, false, &channel);
}

void Audio::Update(float delta)
{
	system->update(); //updating the sound system for every frame
}
