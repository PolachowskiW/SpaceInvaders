#include "Blockade.h"

//function will set bunkers position in the array
Bunker* buildBlockade(int numBunkers)
{	
	//each new bunker is based on pointer to array's index
	Bunker* bunkers = new Bunker[numBunkers];
	
	//game will draw number of bunkers based on number set in main code of the game
	for (int i = 0; i < numBunkers; i++)
	{
		//function sets starting position for each bunker to the same value so it can modify it later
		//to set each bunker on proper position
		float x = 160.0f;
		float y = 790.0f;

		//function calls out "Bunker" class 'spawn' function for each bunker
		bunkers[i].spawn(x + i * 280.0f, y);
	}
	//function returns bunkers so they can be drawn in the arena
	return bunkers;
}