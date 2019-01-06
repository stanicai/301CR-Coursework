#include <sstream>
#include <iostream>

#include "GameState.h"
#include "GameLevel3.h"
#include "GameLevel2.h"
#include "GameValues.h"
#include "Game.h"
#include "Player.h"
#include "Weapon.h"
#include "MyContactListener.h"
#include "RandomWall.h"
#include "HorizontalWall.h"
#include "FPS.h"
#include "GameOver.h"
#include "PauseState.h"

using namespace sf;
using namespace std;

//counters for the walls, enemies and missles, used to go through each of the array elements
int counterLevel2;
int counterLevel21;
int counterLevel22;
int counterLevel23;


//function that outputs a random number that takes a maximum value that it allowed to reach
int randomMethodLevel2(int max)
{
	int randomNo = rand();
	float random = (randomNo%max) + 1;
	int myRandom = random;
	return myRandom;
}

GameLevel2::GameLevel2(GameDataRef data) : _data(data)
{

}

//function to initialised all the elements 
void GameLevel2::Init()
{
	//setting up lua and the file it uses for data
	lua_State* F = luaL_newstate();
	luaL_dofile(F, "level.lua");
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);

	LuaRef lv2 = getGlobal(F, "level2");
	LuaRef lvl2bull = lv2["level2AllBullets"];
	LuaRef lvl2finpt = lv2["level2FinalPoints"];
	LuaRef lvl2enmIS = lv2["level2EnemyInitialSize"];
	LuaRef lvl2enmFS = lv2["level2EnemyFinalSize"];
	LuaRef lvl2PFHAN = lv2["level2PointsForHittingAnEnemy"];
	LuaRef lvl2HT = lv2["level2HealthTakenByEnemy"];

	level2AllBullets = lvl2bull.cast<int>();
	level2FinalPoints = lvl2finpt.cast<int>();
	level2EnemyInitialSize = lvl2enmIS.cast<int>();
	level2EnemyFinalSize = lvl2enmFS.cast<int>();
	level2PointsForHittingAnEnemy = lvl2PFHAN.cast<int>();
	level2HealthTakenByEnemy = lvl2HT.cast<int>();

	//loading the textures and font
	this->_data->assets.LoadTexture("Pause", PAUSE_BUTTON);
	this->_data->assets.LoadTexture("Player", PLAYER_SPRITE);
	this->_data->assets.LoadTexture("Weapon", WEAPON_TEXTURE);
	this->_data->assets.LoadTexture("Enemy", ENEMY_SPRITE);
	this->_data->assets.LoadTexture("Wall", WALL_TEXTURE);
	this->_data->assets.LoadFont("Font", GAME_FONT);

	//assigning the textures
	_background.setTexture(this->_data->assets.getTexture("Background"));
	_player._sprite.setTexture(this->_data->assets.getTexture("Player"));
	_player._weapon.missle.setTexture(&this->_data->assets.getTexture("Weapon"));
	_enemy._sprite.setTexture(this->_data->assets.getTexture("Enemy"));
	_wall.rect.setTexture(&this->_data->assets.getTexture("Wall"));
	_hoWall.rect.setTexture(&this->_data->assets.getTexture("Wall"));
	_pauseButton.setTexture(this->_data->assets.getTexture("Pause"));

	_pauseButton.setPosition(GAME_WINDOW_WIDTH - _pauseButton.getGlobalBounds().width - 10, _pauseButton.getPosition().y + 10);

	//assigning the font
	_player._text.setFont(this->_data->assets.getFont("Font"));
	_player._weapon._text.setFont(this->_data->assets.getFont("Font"));
	_player._weapon._textPoints.setFont(this->_data->assets.getFont("Font"));
	_fps._text.setFont(this->_data->assets.getFont("Font"));

	//setting up the font values for the points and bullets because they are different based on the level
	_player._weapon._text.setString("BULLETS		" + to_string(_player._weapon.bulletsUsed) + "	OF	" + to_string(LEVEL_2_ALL_BULLETS));
	_player._weapon._textPoints.setString("POINTS		" + to_string(_player._weapon.points) + "	OF	" + to_string(LEVEL_2_FINAL_POINTS));

	//setting the font position on the screen
	_player._text.setPosition(10, 0);
	_player._weapon._text.setPosition(10, 25);
	_player._weapon._textPoints.setPosition(10, 50);
	_fps._text.setPosition(10, 75);

	//calling the Init function for all the elemnts in the scene
	_fps.Init();
	_player._weapon.Init();

	//the objects that have box2d colliders must have their bodies and fixtures intialised here otherwise they wouldn't exist
	_player.Init();
	_player._playerMove = world.CreateBody(&_player._playerBD);
	_player._playerMove->CreateFixture(&_player.fixtureDef);

	_enemy.Init();
	_enemy._playerMove = world.CreateBody(&_enemy._playerBD);
	_enemy._playerMove->CreateFixture(&_enemy.fixtureDef);

	_wall.Init();
	_wall.groundBody = world.CreateBody(&_wall.groundBodyDef);
	_wall.groundBody->CreateFixture(&_wall.groundBox, 0.0f);

	_hoWall.Init();
	_hoWall.groundBody = world.CreateBody(&_hoWall.groundBodyDef);
	_hoWall.groundBody->CreateFixture(&_hoWall.groundBox, 0.0f);

	_audio.Init();
}

void GameLevel2::Input()
{
	Event event;
	while (this->_data->window.pollEvent(event))
	{
		if (Event::Closed == event.type)
		{
			this->_data->window.close();
		}
		//checking if the pause button is clicked, and if it is moving to the pause state
		if (this->_data->input.isSpriteClicked(this->_pauseButton, Mouse::Left, this->_data->window))
		{
			this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
		}
	}
}

void GameLevel2::Update(float delta)
{
	world.Step(timeStep, velocityIterations, positionIterations); //initialising the box2d world in order for the colliders and its elements to work in the game
	world.SetContactListener(&myContactListenerInstance);  //the contact listener that checks for collisions

	//the updates for each elemnt present in the scene 
	_fps.Update(delta);
	_player.Update(delta);
	_player._weapon.Update(delta);
	_enemy.Update(delta);
	_wall.Update(delta);
	_hoWall.Update(delta);
	_audio.Update(delta);

	Time elapsed = missleClock.getElapsedTime();  // the elapsed time that works with the weapon delay

	//update for the text 
	_player._weapon._text.setString("BULLETS		" + to_string(_player._weapon.bulletsUsed) + "	OF	" + to_string(LEVEL_2_ALL_BULLETS));
	_player._weapon._textPoints.setString("POINTS		" + to_string(_player._weapon.points) + "	OF	" + to_string(LEVEL_2_FINAL_POINTS));

	//checking if the escape key is pressed to see if the window should be closed or not
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		this->_data->window.close();
	}

	//checking if the amount of bullets used is less than the maximum allowed
	if (_player._weapon.bulletsUsed < LEVEL_2_ALL_BULLETS)
	{
		//checking the time so the bullets could be delayed
		if (elapsed.asSeconds() >= 0.11)
		{
			missleClock.restart();

			//the space bar spawns the bullets 
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				//if the key is pressed the shooting sound plays
				_audio.result1 = _audio.system->playSound(_audio.sound1, NULL, false, &_audio.channel1);

				_player._weapon.bulletsUsed++;
				//setting the position in the center on the player
				_player._weapon.missle.setPosition((_player._sprite.getPosition().x) + (SPRITE_SIZE_WIDTH / 2) - _player._weapon.missle.getGlobalBounds().width / 2, _player._sprite.getPosition().y + SPRITE_SIZE_HIGHT / 2);
				_player._weapon.direction = _player.direction; // used to go in the same direction as the player
				_player.weaponArray.push_back(_player._weapon); //putting each bullet in the array

				//checking if the enemy array size is less than the final size to see if there should be more added when you press space
				if (enemyArray.size() < LEVEL_2_ENEMY_FINAL_SIZE)
				{
					//the posiiton is random for the whole width and height of the screen and there is a body and fixture created for each of the so the colliders could work
					_enemy._playerBD.position.Set(randomMethodLevel2(8), -randomMethodLevel2(5));
					_enemy._playerMove = world.CreateBody(&_enemy._playerBD);
					_enemy._playerMove->CreateFixture(&_enemy.fixtureDef);
					enemyArray.push_back(_enemy);
				}
			}
			//is either one of the arrow keys is used the footstep sound starts
			if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Right))
			{
				_audio.result2 = _audio.system->playSound(_audio.sound2, NULL, false, &_audio.channel2);
			}
		}

	}
	else
	{
		//if there aren't any more bullets available the game is over and it goes to the game over state
		this->_data->machine.AddState(StateRef(new GameOver(_data)), true);
	}

	//This checks for a collision between the Enemies and The Missles by going through both arrays
	//If a collision is encountered, then the bool that checks if any bullets should be deleted is set to true and points are added
	counterLevel2 = 0;
	for (_player.iter = _player.weaponArray.begin(); _player.iter != _player.weaponArray.end(); _player.iter++)
	{
		counterLevel21 = 0;

		for (iterEnemy = enemyArray.begin(); iterEnemy != enemyArray.end(); iterEnemy++)
		{
			if (_player.weaponArray[counterLevel2].missle.getGlobalBounds().intersects(enemyArray[counterLevel21]._sprite.getGlobalBounds()))
			{
				_player.weaponArray[counterLevel2].deleteBullets = true;
				_player._weapon.points += LEVEL_2_POINTS_FOR_HITTING_AN_ENEMY;
			}
			counterLevel21++;
		}
		counterLevel2++;
	}

	//Loop that goes through the weapon array to check if a collision has occured with one of the enemys, to see if any of the missles should be destroyed
	counterLevel2 = 0;
	for (_player.iter = _player.weaponArray.begin(); _player.iter != _player.weaponArray.end(); _player.iter++)
	{
		if (_player.weaponArray[counterLevel2].deleteBullets == true)
		{
			_player.weaponArray.pop_back();
			break;
		}
		counterLevel2++;
	}

	//if the bool from the contact listener that checks if the player collided with an enemy is set to true, you lose a certain amount of health
	if (myContactListenerInstance.playerLosesHP == true)
	{
		if (_player.health > 0)
			_player.health -= LEVEL_2_HEALTH_TAKEN;
		else
			_player.health = 0;
		myContactListenerInstance.playerLosesHP = false;
	}

	//checks if you reached the final points to see if you should go to the next level
	if (_player._weapon.points >= LEVEL_2_FINAL_POINTS)
		this->_data->machine.AddState(StateRef(new GameLevel3(_data)), true);
	//checks if your health is null to see if the game over state should start
	if (_player.health <= 0)
	{
		this->_data->machine.AddState(StateRef(new GameOver(_data)), true);
	}

	//the creation of a fixed amount of walls
	if (vertical == false)
	{
		if (_wall.wallArray.size() > 1)
		{
			//the posiiton is random for the whole width and height of the screen and there is a body and fixture created for each of the so the colliders could work
			_wall.groundBodyDef.position.Set(randomMethodLevel2(8), -randomMethodLevel2(5));
			_wall.groundBody = world.CreateBody(&_wall.groundBodyDef);
			_wall.groundBody->CreateFixture(&_wall.groundBox, 0.0f);
			_wall.wallArray.push_back(_wall);
		}
		else
			_wall.wallArray.push_back(_wall);

		//when it reached this array size it should stop making them
		if (_wall.wallArray.size() > 10)
			vertical = true;
	}

	//the creation of a fixed amount of walls
	if (horizontal == false)
	{
		if (_hoWall.wallHorizontalArray.size() > 1)
		{
			//the posiiton is random for the whole width and height of the screen and there is a body and fixture created for each of the so the colliders could work
			_hoWall.groundBodyDef.position.Set(randomMethodLevel2(9), -randomMethodLevel2(5));
			_hoWall.groundBody = world.CreateBody(&_hoWall.groundBodyDef);
			_hoWall.groundBody->CreateFixture(&_hoWall.groundBox, 0.0f);
			_hoWall.wallHorizontalArray.push_back(_hoWall);
		}
		else
			_hoWall.wallHorizontalArray.push_back(_hoWall);

		//when it reached this array size it should stop making them
		if (_hoWall.wallHorizontalArray.size() > 5)
			horizontal = true;
	}

	//the creation of a fixed amount of enemies
	if (enemyInitialise == false)
	{
		if (enemyArray.size() > 0)
		{
			//the posiiton is random for the whole width and height of the screen and there is a body and fixture created for each of the so the colliders could work
			_enemy._playerBD.position.Set(randomMethodLevel2(8), -randomMethodLevel2(5));
			_enemy._playerMove = world.CreateBody(&_enemy._playerBD);
			_enemy._playerMove->CreateFixture(&_enemy.fixtureDef);
			enemyArray.push_back(_enemy);
		}
		else
			enemyArray.push_back(_enemy);

		//when it reached this array size it should stop making them
		if (enemyArray.size() > LEVEL_2_ENEMY_INITIAL_SPWAN_SIZE)
			enemyInitialise = true;
	}

	//the following if statements are for the player position while going off the screen boundries; it works exactly like pac man
	//if you go on the left out of the screen, you end up in the right side of the screen
	//this is happening for all directions
	//there is a body and fixture created for each of the so the colliders could work
	if (_player._playerGraphicsPosition.x < 0)
	{
		_player._playerBD.position.Set(GAME_WINDOW_WIDTH / scalingFactor, -((_player._playerGraphicsPosition.y / scalingFactor) + _player._playerHalfWidth));
		_player._playerMove = world.CreateBody(&_player._playerBD);
		_player._playerMove->CreateFixture(&_player.fixtureDef);
	}
	else if (_player._playerGraphicsPosition.x > GAME_WINDOW_WIDTH)
	{
		_player._playerBD.position.Set(_player._playerHalfWidth, -((_player._playerGraphicsPosition.y / scalingFactor) + _player._playerHalfWidth));
		_player._playerMove = world.CreateBody(&_player._playerBD);
		_player._playerMove->CreateFixture(&_player.fixtureDef);
	}
	else if (_player._playerGraphicsPosition.y < 0)
	{
		_player._playerBD.position.Set(((_player._playerGraphicsPosition.x / scalingFactor) + _player._playerHalfWidth), -(GAME_WINDOW_HIGHT / scalingFactor));
		_player._playerMove = world.CreateBody(&_player._playerBD);
		_player._playerMove->CreateFixture(&_player.fixtureDef);
	}
	else if (_player._playerGraphicsPosition.y > GAME_WINDOW_HIGHT)
	{
		_player._playerBD.position.Set((_player._playerGraphicsPosition.x / scalingFactor) + _player._playerHalfWidth, -_player._playerHalfWidth);
		_player._playerMove = world.CreateBody(&_player._playerBD);
		_player._playerMove->CreateFixture(&_player.fixtureDef);
	}
}

void GameLevel2::Draw(float delta)
{
	this->_data->window.clear(Color::Black);

	//drawing the background, pause button and the player sprite
	this->_data->window.draw(this->_background);
	this->_data->window.draw(this->_pauseButton);
	this->_data->window.draw(_player._sprite);


	//drawing of arrays for walls, enemys and bullets
	counterLevel2 = 0;
	for (_player.iter = _player.weaponArray.begin(); _player.iter != _player.weaponArray.end(); _player.iter++)
	{
		_player.weaponArray[counterLevel2].Update(delta);
		this->_data->window.draw(_player.weaponArray[counterLevel2].missle);
		counterLevel2++;
	}
	counterLevel21 = 0;
	for (iterEnemy = enemyArray.begin(); iterEnemy != enemyArray.end(); iterEnemy++)
	{
		enemyArray[counterLevel21].Update(delta);
		this->_data->window.draw(enemyArray[counterLevel21]._sprite);
		counterLevel21++;
	}
	counterLevel22 = 0;
	for (_wall.iterWall = _wall.wallArray.begin(); _wall.iterWall != _wall.wallArray.end(); _wall.iterWall++)
	{
		_wall.wallArray[counterLevel22].Update(delta);
		this->_data->window.draw(_wall.wallArray[counterLevel22].rect);
		counterLevel22++;
	}
	counterLevel23 = 0;
	for (_hoWall.iterHorizontalWall = _hoWall.wallHorizontalArray.begin(); _hoWall.iterHorizontalWall != _hoWall.wallHorizontalArray.end(); _hoWall.iterHorizontalWall++)
	{
		_hoWall.wallHorizontalArray[counterLevel23].Update(delta);
		this->_data->window.draw(_hoWall.wallHorizontalArray[counterLevel23].rect);
		counterLevel23++;
	}

	// TEXT DRAWING
	this->_data->window.draw(_player._text);
	this->_data->window.draw(_player._weapon._text);
	this->_data->window.draw(_player._weapon._textPoints);
	this->_data->window.draw(_fps._text);

	this->_data->window.display();
}
