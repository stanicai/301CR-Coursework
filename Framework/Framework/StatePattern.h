/* "Allow an object to alter its behaviour when its internal state changes. The object will
appear to change its class." */

#pragma once
#include <SFML\Graphics.hpp>

/* We forward declare our Entity so the compiler doesn't complain when State includes it as
a function argument */

class Entity;

/* This is our base State class. The important element here is the universal Update function
which all child classes of state will inherit - each will have its own unique update, but the
input argument will remain the same for our example */

class State
{
public:
	State() {};
	virtual ~State() {};
	virtual void update(Entity* entity) {};
};

/* Now the proper Entity class. Note the pointers to Physics and State. It should be easy
to visualise how this might extend to graphics information, gameplay, even control patterns */

class Entity {
public:
	virtual ~Entity() {};
	virtual void setState(State* newState) { entityState = newState; };
	virtual PhysicsData* getPhysics() { return entityPhysics; };
	virtual void setPhysics(PhysicsData* physicsData) { entityPhysics = physicsData; };

protected:
	PhysicsData * entityPhysics;
	State* entityState;
};

/* Child classes of state which illustrate our FSM - as they inherit from state, our
Entity can populate its entityState variable with a memory address to any of them.
Since update() is common to all children of State, this approach makes it very simple
to govern entity behaviour. In addition, it grants a level of modularity, where removing
or editing one state doesn't necessary require edits to others. */

class StopState : public State {
public:
	StopState() {};
	virtual ~StopState() {};
	virtual void update(Entity* entity) {
		entity->getPhysics()->setVelocity(sf::Vector2f(0.0f, 0.0f));
	}
};

class MoveUpState : public State
{
public:
	MoveUpState() {};
	virtual ~MoveUpState() {};
	virtual void update(Entity* entity) {
		entity->getPhysics()->setVelocity(sf::Vector2f(0.0f, -5.0f));
	}
};

class MoveDownState : public State
{
public:
	MoveDownState() {};
	virtual ~MoveDownState() {};
	virtual void update(Entity* entity) {
		entity->getPhysics()->setVelocity(sf::Vector2f(0.0f, 5.0f));
	}
};

class MoveLeftState : public State
{
public:
	MoveLeftState() {};
	virtual ~MoveLeftState() {};
	virtual void update(Entity* entity) {
		entity->getPhysics()->setVelocity(sf::Vector2f(-5.0f, 0.0f));
	}
};

class MoveRightState : public State
{
public:
	MoveRightState() {};
	virtual ~MoveRightState() {};
	virtual void update(Entity* entity) {
		entity->getPhysics()->setVelocity(sf::Vector2f(5.0f, 0.0f));
	}
};

/* Static declarations of each state type. We've made these global, for ease of
demonstration, but obviously you wouldn't in your project! What matters here is that
there is a static instance of each type of state our Cat might wind up in, allowing us
to pass in that reference and thus call the appropriate update function.

This also saves us from declaring additional instances of states which are common to
multiple entities. It should be easy to imagine how a Goomba in Mario Brothers could map
to two of these states, for example, simply with different triggers to those the player
avatar uses to switch between them. */

static StopState stop;
static MoveUpState up;
static MoveDownState down;
static MoveLeftState l;
static MoveRightState r;

/* These states are very simplistic, and they get one thing wrong - the logic to change
state is externalised. Below is an example of a 'proper' state which includes all of the
requisite logic: */

class ProperState
{
public:
	ProperState() {};
	virtual ~ProperState() {};
	virtual void update(sf::Event e, Entity* entity) {};
};


class ProperStopState : public ProperState {
	ProperStopState() {};
	virtual ~ProperStopState() {};
	virtual void update(sf::Event e, Entity* entity) {
		if(e.type == sf::Event::KeyPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				entity->setState(&l);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				entity->setState(&r);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				entity->setState(&up);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				entity->setState(&down);
			}
		}
		else {
			entity->getPhysics()->setVelocity(sf::Vector2f(0.0f, 0.0f));
		}
	}
};

/* Our Cat entity!*/

class Cat : public Entity {
public:
	virtual ~Cat() {};
	virtual void setState(State* newState) { entityState = newState; };
	virtual State* getState() { return entityState; };
	virtual PhysicsData* getPhysics() { return entityPhysics; };
	virtual void setPhysics(PhysicsData* physicsData) { entityPhysics = physicsData; };
};

