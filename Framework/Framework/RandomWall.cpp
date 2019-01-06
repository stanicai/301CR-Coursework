#include "RandomWall.h"
#include "Player.h"


RandomWall::RandomWall(GameDataRef data): _data(data)
{

}

RandomWall::RandomWall()
{
}

RandomWall::~RandomWall()
{
}

//function that outputs a random number that takes a maximum value that it allowed to reach
int RandomWall::randomMethod(int max)
{
	int randomNo = rand();
	float random = (randomNo%max) + 1;
	int myRandom = random;
	return myRandom;
}

void RandomWall::Init()
{
	//setting up the rectangle size and position
	rect.setSize(sf::Vector2f(400,100));
	rect.setPosition(0.0f, 500.0f);

	groundBox.SetAsBox(groundHalfWidth, groundHalfHeight);

	//this is the position in meters on the x and y axis
	groundBodyDef.position.Set(randomMethod(9), -randomMethod(5));

	//setting up the graphic position based on the physics and half of its width; 
	//it is multiplied with the scaling factor so it would be converted back to the pixel size so its position would match the sfml requirements
	groundGraphicsPosition.x = (groundPhysicsPosition.x - groundHalfWidth)*scalingFactor;
	groundGraphicsPosition.y = (groundPhysicsPosition.y + groundHalfHeight)*scalingFactor*-1.0f;

	//setting the sprite position 
	rect.setPosition(groundGraphicsPosition);
}

void RandomWall::Update(float delta)
{
	world.Step(timeStep, velocityIterations, positionIterations);

	groundPhysicsPosition = groundBody->GetPosition();  //the physics position is based on the movement position
	groundGraphicsPosition.x = (groundPhysicsPosition.x - groundHalfWidth)*scalingFactor;
	groundGraphicsPosition.y = (groundPhysicsPosition.y + groundHalfHeight)*scalingFactor*-1.0f;

	rect.setPosition(groundGraphicsPosition);
}

