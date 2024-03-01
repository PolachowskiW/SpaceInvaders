//defining 'creteHorde' function
#include "Horde.h"

//function will set invaders position in the array and will assign proper texture to invaders based on their type
//(type is being taken from "Invader"'s class 'spawn' function that operates switch assigning proper textures to invaders based on their 
//index number)
Invader* createHorde(int numInvaders)
{
	//each new invader is based on pointer from vertex array
	Invader* invaders = new Invader[numInvaders];
	
	//game will draw and set number of invaders defined in main code of the game
	for (int i = 0; i < numInvaders; i++)
	{	
		//function sets starting position for each invader to the same value so it can modify it later
		//to set each invader on proper position
		float x = 250.0f;
		float y = 96.0f;
		int type;

		//invaders are displayed in 2D array
		//loop draws invaders in rows instead of columns so assigning number of points for each invader is easier to set
		for (int w = 0; w < 5; w++)
		{
			for (int h = 0; h < 11; h++)
			{	
				//game uses row number to determine which type of invaders to draw in given row
				if (w == 0)
				{
					type = 2;
				}
				else if (w == 1 || w == 2)
				{
					type = 1;
				}
				else 
				{
					type = 0;
				}

				//function calls out "Invader" class 'spawn' sunction for every invader
				invaders[i].spawn(x + h * 80.0f, y + w * 62.0f, type);
				i++;
			}
		}
		//function returns invaders so they can be drawn on the arena
		return invaders;
	}
}
