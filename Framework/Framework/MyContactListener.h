#pragma once
#include <sstream>
#include <iostream>

#include <Box2D\Box2D.h>
#include "Enemy.h"

using namespace std;

class MyContactListener : public b2ContactListener
{
public:
	bool playerLosesHP = false;
	bool playerGetsPoints = false;

	void BeginContact(b2Contact* contact) {

		//check if fixture A was a player
		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		if (bodyUserData == "player")
		{		//check if fixture B was an enemy
			bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
			if (bodyUserData == "enemy")
			{
				playerLosesHP = true;
			}
		}
		else if (bodyUserData == "enemy")
		{
			bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
			if (bodyUserData == "player")
			{
				playerLosesHP = true;
			}
		}
	}
};