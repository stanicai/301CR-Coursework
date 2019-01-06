#include "Entity.h"

//function that outputs a random number that takes a maximum value that it allowed to reach
int Entity::randomMethod(int max)
{
	int randomNo = rand();
	float random = (randomNo%max) + 1;
	int myRandom = random;
	return myRandom;
}
