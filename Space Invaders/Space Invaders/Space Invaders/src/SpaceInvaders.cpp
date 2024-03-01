#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Invader.h"
#include "Horde.h"
#include "TextureHolder.h"
#include "Bullet.h"
#include "InvaderBullet.h"
#include "Bunker.h"
#include "Blockade.h"
#include "lives.h"
#include "LivesDisplay.h"
#include "RedInvader.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>


using namespace sf;
using namespace std;

int main() 
{
	TextureHolder holder;

	// All states that game can be in
	enum class State
	{
		PAUSED, GAME_OVER, PLAYING, MENU, WIN, MAIN
	};
	// Sets starting state of the game to main(title) screen
	State state = State::MAIN;
	

	Vector2f resolution;
	//setting game's resolution
	resolution.x = 1280;
	resolution.y = 1000;

	//random number generator used for randomizing amount of points player gets after shooting down red invader
	//Also used to randomly choose one of invaders to take the shot agains a player
	srand(time(NULL));
	
	//int generated by RN generator. Used to tell Invader shot function which invader takes a shot
	int InvaderShot;

	//setting up a game window
	RenderWindow window(VideoMode(resolution.x, resolution.y),"Space Invaders", Style::Default);

	// setting clock and timer used for timed events such as player and invaders updating and invader shots
	Clock clock;
	Time gameTimeTotal;
	
	//instance of player
	Player player;
	//instance of red invader
	RedInvader redInvader;

	/*Vector2f position;*/

	//boolean controlling invaders array movement direction
	bool InvaderMove = true;
	
	//number of invaders in array
	int numInvaders;
	//number of invaders alive controlling a game loop. If it's 0, game enters 'WIN' state
	int numInvadersAlive;
	Invader* invaders = nullptr;
	
	//number of bunkers in array
	int numBunkers;
	Bunker* bunkers = nullptr;

	//number of lives represented by player sprite to be drwn in an array
	//Updated every frame and is always equal to players current health
	int numLives;
	Lives* lives = nullptr;
	
	//array of bullets player holds
	//due to complications with implementation of shooting system it'll be described better in test report
	Bullet bullets[10];
	int currentBullet = 0;

	//instance of invader's bullet
	InvaderBullet InvaderBullets;
	int IcurrentBullet = 0;
	
	//int that holds number of points player gets after shooting down red invader
	//generated by RN generator 
	int RedInvaderPoints;

	//timer that holds last time player pressed spacebar to take a shot
	//used in regulation of player's rate of fire
	Time lastPressed;
	
	//ints holding current game's score and the highscore. Game uses those to first gather all the points player got and then check
	//if high score has been beaten. High score is later being exported to 'scores.txt' document
	int score = 0;
	int hiScore = 0;

	//instance of font used by the game to write score on the screen
	Font font;
	font.loadFromFile("assets\\fonts\\unifont.ttf");

	//Setting a score text
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(40);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(Vector2f(890, 950));

	//Setting End Score
	Text EndScoreText;
	EndScoreText.setFont(font);
	EndScoreText.setCharacterSize(65);
	EndScoreText.setFillColor(Color::White);
	EndScoreText.setPosition(Vector2f(480, 630));

	//Load High Score from text file
	ifstream inputFile("HiScores\\scores.txt");
	if (inputFile.is_open())
	{
		inputFile >> hiScore;
		inputFile.close();
	}

	//Setting highscore
	Text hiScoreText;
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(55);
	hiScoreText.setFillColor(Color::White);
	hiScoreText.setPosition(1400, 0);
	std::stringstream s;s << "Hi Score:" << hiScore;
	hiScoreText.setString(s.str());

	//buffering and loading invader's bullet sound
	SoundBuffer IbulletBuffer;
	IbulletBuffer.loadFromFile("assets\\sounds\\InvaderBullet.wav");
	Sound s_InvaderBullet;
	s_InvaderBullet.setBuffer(IbulletBuffer);

	//buffering and loading invader being hit sound
	SoundBuffer InvaderHitBuffer;
	InvaderHitBuffer.loadFromFile("assets\\sounds\\InvaderHit.wav");
	Sound s_InvaderHit;
	s_InvaderHit.setBuffer(InvaderHitBuffer);

	//buffering and loading player's bullet sound
	SoundBuffer pBulletBuffer;
	pBulletBuffer.loadFromFile("assets\\sounds\\ShipBullet.wav");
	Sound s_PlayerBullet;
	s_PlayerBullet.setBuffer(pBulletBuffer);

	//buffering and loading player being hit sound
	SoundBuffer PlayerHitBuffer;
	PlayerHitBuffer.loadFromFile("assets\\sounds\\ShipHit.wav");
	Sound s_PlayerHit;
	s_PlayerHit.setBuffer(PlayerHitBuffer);

	//loading graphics of game's main screen
	Sprite MainScreen;
	Texture TextureMainScreen = TextureHolder::GetTexture("assets\\images\\main.png");
	MainScreen.setTexture(TextureMainScreen);
	
	//loading graphics of game's menu screen
	Sprite MenuScreen;
	Texture TextureMenuScreen = TextureHolder::GetTexture("assets\\images\\menu.png");
	MenuScreen.setTexture(TextureMenuScreen);

	//loading graphics of game's pause screen
	Sprite PauseScreen;
	Texture TexturePauseScreen = TextureHolder::GetTexture("assets\\images\\pause.png");
	PauseScreen.setTexture(TexturePauseScreen);

	//loading graphics of game's win screen
	Sprite WinScreen;
	Texture TextureWinScreen = TextureHolder::GetTexture("assets\\images\\win.png");
	WinScreen.setTexture(TextureWinScreen);

	//loading graphics of game's 'game over' screen
	Sprite GameOverScreen;
	Texture TextureGameOverScreen = TextureHolder::GetTexture("assets\\images\\GameOver.png");
	GameOverScreen.setTexture(TextureGameOverScreen);

	//creating a lower boundary
	// this boundry will check if invaders have reached past player's position and if so, game will be put in "GAME_OVER' state
	RectangleShape boundary;
	boundary.setSize(Vector2f(1280.f, 78.f));
	boundary.setOrigin(Vector2f(640.f, 39.f));
	boundary.setPosition(Vector2f(640.f, 961.f));
	boundary.setFillColor(Color::Black);
	FloatRect boundryLine = boundary.getGlobalBounds();

	//Left bound that helps to control movement of invaders array
	RectangleShape LeftBound;
	LeftBound.setSize(Vector2f(24.f, 1000.f));
	LeftBound.setOrigin(Vector2f(0.f, 0.f));
	LeftBound.setPosition(Vector2f(-24.f, 0.f));
	LeftBound.setFillColor(Color::White);
	FloatRect LeftBoundLine = LeftBound.getGlobalBounds();

	//Right bound that helps to control movement of invaders array
	RectangleShape RightBound;
	RightBound.setSize(Vector2f(24.f, 1000.f));
	RightBound.setOrigin(Vector2f(0.f, 0.f));
	RightBound.setPosition(Vector2f(1280.f, 0.f));
	RightBound.setFillColor(Color::White);
	FloatRect RightBoundLine = RightBound.getGlobalBounds();

	//green bar that separates HUD from game arena
	RectangleShape bar;
	bar.setSize(Vector2f(1280.f, 20.f));
	bar.setOrigin(Vector2f(640.f, 10.f));
	bar.setPosition(Vector2f(640.f, 915.f));
	bar.setFillColor(Color::Green);

	//Last score update;
	int FramesSinceLastScoreUpdate = 0;

	//frames interval for score update. Used to ensure lower resource consumption by updating score every 1000th frame
	int FpsMeasurementFrameInterval = 1000;

	// The main game loop
	while (window.isOpen())
	{
		//event polling for the game loop
		//setting controls over game screens
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == Event::KeyPressed)
			{	
				//event allowing player to pause a game
				if (event.key.code==Keyboard::Return&&state==State::PLAYING)
				{
					state = State::PAUSED;
				}
				//event allowing player to resume a game
				else if (event.key.code==Keyboard::Return&&state== State::PAUSED)
				{
					state = State::PLAYING;
					//clock gets restarted to prevent any frames update while game is in 'PAUSED' state
					clock.restart();
				
				}
				//transitioning from main screen to menu screen
				else if (event.key.code==Keyboard::Return&&state==State::MAIN)
				{
					state = State::MENU;
				}
				//returning to menu scren after winning a game
				else if (event.key.code == Keyboard::Return && state == State::WIN)
				{
					state = State::MENU;
				}
				//returning to menu screen after losing a game
				else if (event.key.code == Keyboard::Return && state == State::GAME_OVER)
				{
					state = State::MENU;
				}
				if (state == State::PLAYING)
				{

				}
			}
		}// End Event Polling

		//function that allows player to exit the game using 'ESC' key
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		//controlling player's movement and actions in 'PLAYING' state
		if (state==State::PLAYING)
		{
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{	//after pressing and holding down left arrow key game loop calls out "Player" class movement function to change players position
				//every frame
				player.moveLeft();
			}
			else
			{	//when key is released game loop calls out "Player" class function that stops player's movement
				player.stopLeft();
			}
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{	//after pressing and holding down right arrow key game loop calls out "Player" class movement function to change players position
				//every frame
				player.moveRight();
			}
			else
			{	//when key is released game loop calls out "Player" class function that stops player's movement
				player.stopRight();
			}

			//input for player's shooting
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				//loop makes sure that player is able to shoot only once per 600 miliseconds
				if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 600 )
				{	//game loop calls out "Bullet" class 'shoot' function that uses player's current position to spawn a bullet
					bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y);
					currentBullet++;
					if (currentBullet > 9)
					{
						currentBullet = 0;
					}
					//game loop overwrties 'last pressed' with game's total run time to perform next interation of player shooting correctly
					lastPressed = gameTimeTotal;
					//game loop playes sound of player shooting every time player presses spacebar to shoot
					s_PlayerBullet.play();
					cout << "Bullet has been shot" << endl;
				}
			}

		}// End Left Right movement

		//setting events to control game in 'MENU' state
		if (state == State::MENU)
		{
			//player can transition into 'PLAYING' state by pressing F1 key
			if (event.key.code == Keyboard::F1)
			{
				state = State::PLAYING;
			}
			//instructions for program to prepare game arena
			if (state == State::PLAYING)
			{
				//game spawns player
				player.spawn();

				//game spawns red invader
				redInvader.spawn();

				//number of invaders to be drawn, updated and displayed
				numInvaders = 55;
				//deleting all previously created invaders to free memory spac from stack
				delete[] invaders;
				//creating invaders array
				invaders = createHorde(numInvaders);
				numInvadersAlive = numInvaders;
				
				//number of bunkers to be drawn, updated and displayed
				numBunkers = 4;
				//deleting all previously created bunkers to free memory spac from stack
				delete[] bunkers;
				//creating bunkers array
				bunkers = buildBlockade(numBunkers);

				//number of lives to be drawn, updated and displayed
				numLives = 3;
				//deleting all previously created lives to free mmory spac from stack
				delete[] lives;
				//creating lives array
				lives = displayLives(numLives);

				//resetting player's helath
				player.resetPlayerStats();
				redInvader.resetRedInvaderStats();

				//restarting a clock so the gam doesn't update any frames before drawing first frame of 'PLAYING' state
				clock.restart();

			}

			//displaying graphics for main menu
			window.draw(MainScreen);
		}// Exit MENU

		//instructions for controlling game in 'PLAYING' state
		if (state == State::PLAYING)
		{
			//resetting game's timer
			Time dt = clock.restart();

			//run time of the game
			//used to controll player's and invaders shooting functions
			gameTimeTotal += dt;

			float dtAsSeconds = dt.asSeconds();

			//game updates player instance each frame using function of "Player" class
			player.update(dtAsSeconds);

			//updating red invader
			//occurs only if invader has not been shot
			if (redInvader.isAlive())
			{
				//game updates red invader instance each frame using function of "RedInvader" class
				redInvader.update(dtAsSeconds);
			}
			
			//game gets global bounds of player's sprite for collission detecton calling out "Player" class function
			Vector2f playerPosition(player.getCenter());

			//update invaders position every frame
			for (int i = 0; i < numInvaders; i++)
			{
				//only invaders that have not been shot are being updated
				if (invaders[i].isAlive())
				{	
					//game loop calls out "Invader" class function to determine and set invaders horizontal movement direction
					//game loop is constructed in the way that invaders will always move to the right at the beginning of every loop
					invaders[i].moveRight(dtAsSeconds, InvaderMove);
					
					//loop checks if any of invaders that are alive touched right bound
					if (invaders[i].getBounds().intersects(RightBoundLine))
					{	//everytime bound has been reached, all invaders are being moved towards the player
						for (int j = 0; j < numInvaders; j++)
						{	//calling out "Invader" class function that moves all invaders towards player's position
							invaders[j].descend();
						}
						//change of movement condition. triggers change of horizontal movement direction of all invaders
						InvaderMove = false;
						
					}

					//game loop calls out "Invader" class function that check if conditions have been met to change horizontal movement 
					//direction of all invaders
					invaders[i].moveLeft(dtAsSeconds, InvaderMove);
					//loop checks if any of invaders that are alive touched left bound
					if (invaders[i].getBounds().intersects(LeftBoundLine))
					{	//everytime bound has been reached, all invaders are being moved towards the player
						for (int j = 0; j < numInvaders; j++)
						{	//calling out "Invader" class function that moves all invaders towards player's position
							invaders[j].descend();
						}
						//change of movement condition. triggers change of horizontal movement direction of all invaders
						InvaderMove = true;
					}
				}	
			}//End updating invaders every frame

			//Updating bunkers every frame
			for (int i = 0; i < numBunkers; i++)
			{
				//game loop updates only bunkers that have not been destroyed
				if (bunkers[i].isAlive())
				{	//game loop calls out "Bunker" class function to update bunkers each frame
					bunkers[i].update(dt.asSeconds());
				}
			}//End updating bunkers

			// Make random, alive, invader shoot a bullet
			if (gameTimeTotal.asMilliseconds() % 800 == 0)
			{
				//game loop generates random number from 0 to 54 (index of invaders array) to determine which invaders will shoot
				InvaderShot = rand() % 55;
				
				//game loop will call out "Invader" class 'shoot' function when invader with index number that has been generated
				//has not been chot
				if (invaders[InvaderShot].isAlive())
				{	//game loop calls out "invader" class 'shoot' function that spawns a bullet at randomly chosen invader's position
					InvaderBullets.shoot(invaders[InvaderShot].getCenter().x, invaders[InvaderShot].getCenter().y);
					//game loop playes a sound of invader taking a shot the moment game spawns a bullet
					s_InvaderBullet.play();
					//output for console allows to detect which invader took a shot. Used for debugging purposes e.g. invader took a shot but
					//bullet didn't spawn
					cout << "Invader " << InvaderShot << " shoots" << endl;
				}			
			}//End invader shooting

			//updating every frame for player's bullets
			for (int i = 0; i < 10; i++)
			{	// game will only updaet bullet if it's been spawned by pressing spacebar
				if (bullets[i].isInFlight())
				{	//game loop calls out "Bullet" class function that updates player's bullet every frame
					bullets[i].update(dtAsSeconds);
				}
			}//End player's bullets update

			//updating every frame for invaders bullets
			if (InvaderBullets.isInFlight())
			{
				InvaderBullets.update(dtAsSeconds);
			} // end invader bullet update
		
			// detecting if invader has been shot
			//game loop check if any of bullets stored by player hits any invader
			for (int i = 0; i < 10; i++)
			{	//game loop performs a check on every invader that was drawn
				for (int j = 0; j < numInvaders; j++)
				{	// game will only check bullets that are currently being updated and invaders that has not been shot yet
					if (bullets[i].isInFlight() && invaders[j].isAlive())
					{	//game checks if bullet intersects with invader
						if (bullets[i].getPosition().intersects(invaders[j].getBounds()))
						{	//if invader gets hit bullet update stops after game loop calls out "Bullet" class 'stop' function
							//game loop plays sound of invader being hit when conditions are being met
							bullets[i].stop();
							s_InvaderHit.play();
							//with each shot down invader game loop calls out "Invader" class 'SpeedBoost' function
							//of all invaders that are still alive
							for (int k = 0; k < numInvaders; k++)
							{
								invaders[k].SpeedBoost();
							}
							//game checks if invader has been hit by the bullet and assigns number of points depending on the row 
							//invader has been drawn in
							if (invaders[j].hit())
							{	//invaders in the top most row give player 30 points each
								//'if' statement uses invaders index in the array to determine which row they are drawn into
								if (j >= 0 && j <= 10)
								{
									score += 30;
									cout << "Player gets 30 points" << endl;
								}
								//invaders in 2nd and 3rd row give player 20 points each
								//'if' statement uses invaders index in the array to determine which row they are drawn into
								if (j >= 11 && j <= 32)
								{
									score += 20;
									cout << "Player gets 20 points" << endl;
								}
								//invaders in 4th and 5th row give player 10 points each
								//'if' statement uses invaders index in the array to determine which row they are drawn into
								if (j >= 33 && j <= 54)
								{
									score += 10;
									cout << "Player gets 10 points" << endl;
								}
								//game loop checks if player's current score is higher than current High Score
								if (score >= hiScore)
								{	// if player's current score is higher than current High Score, game overwrites High Score with player's current score
									hiScore = score;
								}
								//after invader has been shot down, game decrements number of invaders still in the arena
								numInvadersAlive--;
								//after all invaders has been shot down, game changes it's state to "WIN" state
								if (numInvadersAlive == 0)
								{
									state = State::WIN;
									//after winning a game, game exports highscore to 'scores.txt' file
									ofstream outputFile("HiScores\\scores.txt");
									outputFile << hiScore;
									outputFile.close();
								}
								//consol outputs for invaders getting shot down and player receiving points for shooting invaders down.
								//Used for debugging purpose e.g. invaders gets shot but is still visible on screen and gets updated or 
								//player shoots down invader in 3rd row but gets wrong amount of points
								cout << "Invader " << j << " has been shot down!" << endl;
								cout << "Player has " << score << " points" << endl;
							}
						}
					}
				}
			}
			//End checking invaders being shot

			//have player been shot
			if (player.getPosition().intersects(InvaderBullets.getPosition()))
			{	//game calls out "Player" class 'hit' function that uses game's total run time to
				//register player getting shot by invader and make sure player can't be shot few times during set amount of time
				if (player.hit(gameTimeTotal))
				{	//console output. Used for debugging purposes
					//e.g. player gets shot but number of lives displayed doesn't change
					cout << "Player got hit!" << endl;
					//if player gets shot, their number of lives decrements
					numLives--;
					//if player gets hit and loses health point, game loop plays sound of player getting shot
					s_PlayerHit.play();
				}
				//if player's health gets to 0, game loop changes game's state to "GAME_OVER" state
				if (player.getHealth() <= 0)
				{
					state = State::GAME_OVER;
					//game writes down highscore to 'scores.txt' file
					ofstream outputFile("HiScores\\scores.txt");
					outputFile << hiScore;
					outputFile.close();
					score = 0;
				}
			} // End checking for player hit
			
			//Checking if Red Invader has been shot
			for (int i = 0; i < 9; i++)
			{	//game checks if any of player's bullet is currently being updated
				if (bullets[i].isInFlight())
				{	//game checks if any of player's bullet in flight intersects with bounds of red invader
					if (redInvader.getBounds().intersects(bullets[i].getPosition()))
					{	//if bullet intersects with red invader bounds bullet stops updating every frame
						//and game loop calls "RedInvader" class 'hit' function
						bullets[i].stop();
						redInvader.hit();
						//after red invader has been shot game awards player with randomly generated amount of points
						//between 100 and 500 points
						RedInvaderPoints = rand() % 401 + 100;
						//game plays sound of invader getting hit
						s_InvaderHit.play();
						//score gets incremented by the amount of points generated by RN generator
						score += RedInvaderPoints;
						cout << "Player got " << RedInvaderPoints << " points" << endl;
					}
				}
				
			}//End Red Invader's check
			

			//Have invaders reach boundary?
			for (int i = 0; i < numInvaders; i++)
			{	
				if (invaders[i].isAlive())
				{	//game checks if any of invaders that are still alive touched lower bounds
					if (invaders[i].getBounds().intersects(boundryLine))
					{	//if any invader reached the bottom of the arena game changes it's state to "GAME_OVER"
						state = State::GAME_OVER;
						//game exports High Score to 'scores.txt' file
						ofstream outputFile("HiScores\\scores.txt");
						outputFile << hiScore;
						outputFile.close();
						score = 0;
					}
				}
			}

			//have blockade been shot
			for (int i = 0; i < numBunkers; i++)
			{	//game checks if currently checked bunker still has more than 0 health points
				if (bunkers[i].isAlive())
				{	//game checks if invaders bullet intersects with a bunker's bounds
					if (bunkers[i].getBounds().intersects(InvaderBullets.getPosition()))
					{	//game calls out "Bunker" class 'hit' function that controls damage dealt to bunkers
						bunkers[i].hit(gameTimeTotal);
						//if bullet intersects with bunker it's no longer being updated
						InvaderBullets.stop();
					}
				}
				
			}
			// End checking for blockade hit

			//increments number of frames since last update to make sure scores and texts are updated every second instead every milisecond			
			FramesSinceLastScoreUpdate++;
			//if second has passed, game will execute instructions below
			if (FramesSinceLastScoreUpdate > FpsMeasurementFrameInterval)
			{
				//Update text
				stringstream ssScore;
				stringstream ssHiScore;
				stringstream ssEndScore;

				//Update the score text
				//game overwrites current score each second with updated score
				ssScore << "SCORE: " << score;
				scoreText.setString(ssScore.str());

				//Update the End Score
				//game overwrites current end score each second with updated score
				ssEndScore << "SCORE: " << score;
				EndScoreText.setString(ssEndScore.str());

				//Update the Highscore text
				//game overwrites current High score each second with updated High score
				ssHiScore << "HI SCORE: " << hiScore;
				hiScoreText.setString(ssHiScore.str());
				//after each update game resets frames back to zero so update can commence after another second
				FramesSinceLastScoreUpdate = 0;
			}//End score update

		}// End Scene Update

		if (state == State::PLAYING)
		{	//preparing window to draw elements of the game
			window.clear();
			//drawing left and right bounds
			window.draw(LeftBound);
			window.draw(RightBound);

			//drawing all invaders
			for (int i = 0; i < numInvaders; i++)
			{
				if (invaders[i].isAlive())
				{
					window.draw(invaders[i].getSprite());
				}
			}

			//drawing all bunkers
			for (int i = 0; i < numBunkers; i++)
			{
				if (bunkers[i].isAlive())
				{
					window.draw(bunkers[i].getSprite());
				}	
			}

			//drawing all bullets
			for (int i = 0; i < 9; i++)
			{
				if (bullets[i].isInFlight())
				{
					window.draw(bullets[i].getShape());
				}	
			}
			
			//drawing invaders bullet
			for (int i = 0; i < 449; i++)
			{
				if (InvaderBullets.isInFlight())
				{
					window.draw(InvaderBullets.getShape());
				}
			}

			//drawing player Sprite
			if (player.getHealth() != 0)
			{
				window.draw(player.getSprite());
			}
			
			//drawing red invader
			if (redInvader.isAlive())
			{
				window.draw(redInvader.getSprite());
			}

			window.draw(boundary);
			window.draw(bar);

			//displaying player's lives
			for (int i = 0; i < numLives; i++)
			{
				window.draw(lives[i].getSprite());
			}

			//drawing current score and high score
			window.draw(scoreText);
			window.draw(hiScoreText);

		}
		if (state == State::MENU)
		{	//when in MENU state game will display menu screen
			window.draw(MenuScreen);
		}
		if (state == State::PAUSED)
		{	//when in PAUSED state game will display pause screen
			window.draw(PauseScreen);
		}
		if (state == State::MAIN)
		{	//when in MAIN state game will display main screen
			window.draw(MainScreen);
		}
		if (state == State::WIN)
		{	//when in WIN state game will display win screen and accumulated points
			window.draw(WinScreen);
			window.draw(EndScoreText);
		}
		if (state == State::GAME_OVER)
		{	//when in GAME_OVER state game will display 'game over' screen and accumulated points
			window.draw(GameOverScreen);
			window.draw(EndScoreText);
		}
		//after drawing all game objects, window will display proper elements depending on the state the game is currently in
		window.display();


	}//End game Loop

	return 0;
}



