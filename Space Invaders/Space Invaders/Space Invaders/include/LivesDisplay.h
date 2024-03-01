//creating "displayLives" function
#pragma once
#include "lives.h"

//'displayLives' function will use pointers to create an array of lives
Lives* displayLives(int numLives)
{
	//each new live is created based on pointer to position in vertex array
	Lives* lives = new Lives[numLives];
	
	//function goes throug each life to set it's position and spawn it using "lives" class 'spawn' function
	for (int i = 0; i < numLives; i++)
	{
		//loop sets starting position for each life so they can be later spawned with equal spacing
		float x = 90.0f;
		float y = 952.0f;

		//game spans lives using position baset on the number of each life and iteration of the loop
		lives[i].spawn(x + i * 90.0f, y);
	}
	//function returns lives so they can be drawn on the screen
	return lives;
}