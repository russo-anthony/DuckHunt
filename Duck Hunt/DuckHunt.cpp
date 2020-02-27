/*==========================================================   Author:
<Anthony>  <Russo>
Modified By: <Anthony Russo>
Date:        4/15/2016

Course: CSC-215
File:  <Duck Hunt>.cpp
Rev #: 1.0
Description: This program is a new version of Duck Hunt recreated
			 in C++.
============================================================*/
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

using namespace std;

/*Screen Size Constants*/
const int SCR_WIDTH = 1280;
const int SCR_HEIGHT = 720;

/*Define Functions*/
bool CreateGame();
void Close();
void roundInit();
void EventPoll();
void UpdateScore();
Uint32 Timer();

SDL_Texture* LoadTexture(string file);

/*Window Initialization*/
SDL_Window* window = NULL;

/*Variables*/
int Bx = 0;
int By = 0;
int score = 0;
int currentDuck = 0;
int duckSwitchx = 0;
int duckInitialx = 0;
int deltX = 0;
int deltY = 0;
int xStart = 0;
int yStart = 0;
int wingCount = 0;
int roundCount = 1;
int roundReturn = 0;
int shots = 0;
int duckNum = 0;
bool playTitleTheme = true;
bool wingPos = true;
bool gameContinue = false;
bool gamePlay = false;
bool quit = false;
bool newDuck = false;
bool hitDuck = false;
bool forwardFlight = true;
bool roundInitFlag = false;
bool roundShow = true;
bool nextRound = false;
bool quitRound = false;
bool inFlight = true;
bool roundSuccess = false;
bool winRound = false;
double duckSpeed = 0.0;
double duckSpeedx = 0.0;
double gameTime = 0.0;
double beginEndT = 0.0;
double roundStart = 0.0;
double roundTime = 0.0;
string strRound = " ";
string strScore = " ";
Uint32 gameStart;
Uint32 lastTime;
Uint32 cloudT1;
Uint32 cloudT2;
Uint32 cloudT3;
Uint32 roundT1;
Uint32 duckT1;
Uint32 duckT1xF;
Uint32 newDuckT;
Uint32 duckT1x;
Uint32 time;

/*Textures, Surfaces, And Renderer*/
SDL_Renderer* renderer = NULL;
SDL_Surface* roundNumber = NULL;
SDL_Surface* nextRoundS = NULL;
SDL_Surface* newScore = NULL;
SDL_Surface* ammo = NULL;
SDL_Texture* bgMask = NULL;
SDL_Texture* grassMask = NULL;
SDL_Texture* duckUp = NULL;
SDL_Texture* duckDown = NULL;
SDL_Texture* duckUpB = NULL;
SDL_Texture* duckDownB = NULL;
SDL_Texture* logo1 = NULL;
SDL_Texture* logo2 = NULL;
SDL_Texture* cloud = NULL;
SDL_Texture* ammoTexture = NULL;
SDL_Texture* roundNumberDisplay = NULL;
SDL_Texture* nextRoundDisplay = NULL;
SDL_Texture* scoreDisplay = NULL;
SDL_Texture* ammoDisplay = NULL;

/*SDL Objects*/
SDL_Rect screen = { 0, 0, SCR_WIDTH, SCR_HEIGHT };
SDL_Rect startScreen = { 0, 0, SCR_WIDTH, SCR_HEIGHT };
SDL_Rect bgRect = { 0, 0, SCR_WIDTH, SCR_HEIGHT };
SDL_Rect grassRect = { 0, 0, SCR_WIDTH, SCR_HEIGHT };
SDL_Rect duckRect = { -200, 50, 195, 105 };
SDL_Rect duckRect2 = { -400, 150, 195, 105 };
SDL_Rect logoRect = { 440, 160, 400, 200 };
SDL_Rect logoRect2 = { 440, 160, 400, 400 };
SDL_Rect cloud1Rect = { 1150, -50, 250, 200 };
SDL_Rect cloud2Rect = { 500, -30, 250, 200 };
SDL_Rect cloud3Rect = { 0, 10, 250, 200 };
SDL_Rect roundRect = { 550, 300, 200, 100 };
SDL_Rect insertDuck = { NULL, NULL, NULL, NULL };
SDL_Rect tmp = { NULL, NULL, NULL, NULL };
SDL_Rect dispTxt = { 450, 300, 700, 100 };
SDL_Rect dispScore = { 50, 670, 100, 50 };
SDL_Rect dispAmmo = { 1050, 670, 100, 50 };
SDL_Rect dispBul1 = { 1140, 655, 20, 60 };
SDL_Rect dispBul2 = { 1170, 655, 20, 60 };
SDL_Rect dispBul3 = { 1200, 655, 20, 60 };

/*Audio Variables*/
Mix_Music* gunshot = NULL;
Mix_Music* ricochet = NULL;
Mix_Music* titleScreen = NULL;
Mix_Music* roundTheme = NULL;
Mix_Music* click = NULL;
Mix_Music* reload = NULL;

TTF_Font* DHFonts = NULL;

/*Create Color*/
SDL_Color black = { 0, 0, 0 };

/*Vector Of Ducks*/
vector<SDL_Rect> duckVec;

/*SDL Events*/
SDL_Event event;

/*Main Function*/
int main(int argc, char* args[]) 
{
	/*Checks For Initialization Errors*/
	if (!CreateGame()) 
	{
		cout << "Game Could Not Be Created" << endl;
		return -1;
	}

	/*Load bgMask Texture From File*/
	bgMask = LoadTexture("Textures/bgMask.png");

	/*Check For Error Loading bgMask*/
	if (bgMask == NULL)
	{
		cout << "Error Loading bgMask.png" << endl;
		return -1;
	}

	/*Load grassMask Texture From File*/
	grassMask = LoadTexture("Textures/grassMask.png");

	/*Check For Error Loading grassMask*/
	if (grassMask == NULL)
	{
		cout << "Error Loading grassMask.png" << endl;
		return -1;
	}

	/*Load Duck Texture For Wings Down*/
	duckDown = LoadTexture("Textures/wingdown.png");

	/*Load Duck Texture For Wings Up*/
	duckUp = LoadTexture("Textures/wingup.png");

	/*Load Duck Texture For Wings Down Backwards*/
	duckDownB = LoadTexture("Textures/wingdownB.png");

	/*Load Duck Texture For Wings Up Backwards*/
	duckUpB = LoadTexture("Textures/wingupB.png");

	/*Load texture For Logo 1*/
	logo1 = LoadTexture("Textures/Logo1.png");

	/*Load texture For Logo 2*/
	logo2 = LoadTexture("Textures/Logo3.png");

	/*Load Texture For A Cloud*/
	cloud = LoadTexture("Textures/cloud.png");

	/*Load Ammo Texture*/
	ammoTexture = LoadTexture("Textures/bullet.png");

	/*Load Audio Files*/

	/*Gunshot*/
	gunshot = Mix_LoadMUS("Audio/gunshot.wav");

	/*Ricochet*/
	ricochet = Mix_LoadMUS("Audio/ricochetShort.wav");

	/*Ammo Click*/
	click = Mix_LoadMUS("Audio/click.wav");

	/*Reload Ammo*/
	reload = Mix_LoadMUS("Audio/reloadSound.wav");

	/*Title Sound*/
	titleScreen = Mix_LoadMUS("Audio/titleTheme.mp3");

	/*Round Start Theme*/
	roundTheme = Mix_LoadMUS("Audio/roundStart.wav");

	/*Open Font*/
	TTF_Font* DHFont = TTF_OpenFont("duckhunt.ttf", 24);

	/*Create Next Round Surface*/
	nextRoundS = TTF_RenderText_Solid(DHFont, "Press Enter To Proceed To The Next Round", black);

	/*Create Next Round Texture*/
	nextRoundDisplay = SDL_CreateTextureFromSurface(renderer, nextRoundS);

	/*Game Loop*/
	while (!quit) 
	{
		/*While Loop For Checking Event Queue*/
		EventPoll();

		/*Get Game Time From Timer*/
		gameTime = Timer();
		roundTime = gameTime - roundStart - newDuckT;

		/****************************************Begin Start Screen***********************************************/
		if (!gamePlay)
		{
			/*Start Theme*/
			if (playTitleTheme == true)
			{
				Mix_PlayMusic(titleScreen, -1);
				playTitleTheme = false;
			}

			/*Clears The Renderer*/
			SDL_RenderClear(renderer);

			/*Adds bgMask To The Renderer*/
			SDL_RenderCopy(renderer, bgMask, &screen, &bgRect);

			/*Adds All Clouds To The Renderer*/
			SDL_RenderCopy(renderer, cloud, &screen, &cloud1Rect);
			SDL_RenderCopy(renderer, cloud, &screen, &cloud2Rect);
			SDL_RenderCopy(renderer, cloud, &screen, &cloud3Rect);

			if (wingPos == true)
			{
				/*Add Ducks One And Two To The Renderer In Wings Up Position*/
				SDL_RenderCopy(renderer, duckUp, &screen, &duckRect);
				SDL_RenderCopy(renderer, duckUp, &screen, &duckRect2);
			}
			else
			{
				/*Add Ducks One And Two To The Renderer In Wings Down Position*/
				SDL_RenderCopy(renderer, duckDown, &screen, &duckRect);
				SDL_RenderCopy(renderer, duckDown, &screen, &duckRect2);
			}

			if (wingPos == true)
			{
				/*Adds Logo1 To The Renderer*/
				SDL_RenderCopy(renderer, logo1, &screen, &logoRect);

			}
			else
			{
				/*Adds Logo2 To The Renderer*/
				SDL_RenderCopy(renderer, logo2, &screen, &logoRect2);

			}

			/*Adds grassMask To The Renderer*/
			SDL_RenderCopy(renderer, grassMask, &screen, &grassRect);

			/*Shows The Rendered Image*/
			SDL_RenderPresent(renderer);

			/*Function To Move The Ducks*/
			duckRect.x = (gameTime - lastTime) * 0.5 - 300;
			duckRect2.x = (gameTime - lastTime) * 0.5 - 600;

			/*Function To Move The Clouds*/
			cloud1Rect.x = ((gameTime - cloudT1) * -0.1 + 1300);
			cloud2Rect.x = ((gameTime - cloudT2) * 0.07) - 400;
			cloud3Rect.x = ((gameTime - cloudT3) * -0.09 + 1800);

			wingCount++;

			if ((wingCount % 1000) == 0)
			{
				if (wingPos == true)
				{
					wingPos = false;
				}
				else
				{
					wingPos = true;
				}
			}

			/*Duck Position Reset*/
			if (duckRect2.x > SCR_WIDTH)
			{
				duckRect.x = -200;
				duckRect2.x = -400;
				lastTime = Timer();
			}

			/*Cloud Position Resets*/

			/*Cloud 1*/
			if (cloud1Rect.x < -400)
			{
				cloud1Rect.x = 1600;
				cloudT1 = Timer();
			}

			/*Cloud 2*/
			if (cloud2Rect.x > 1300)
			{
				cloud2Rect.x = -300;
				cloudT2 = Timer();
			}

			/*Cloud 3*/
			if (cloud3Rect.x < -300)
			{
				cloud3Rect.x = 1600;
				cloudT3 = Timer();
			}
		}

		/***********************************************End Start Screen********************************************************/

		/***********************************************Next Round Check********************************************************/
		
		/*Loop For Entering Next Round*/
		if (nextRound == true)
		{
			/*Display Next Round Prompt*/

			/*Clears The Renderer*/
			SDL_RenderClear(renderer);

			/*Adds bgMask To The Renderer*/
			SDL_RenderCopy(renderer, bgMask, &screen, &bgRect);

			/*Adds All Clouds To The Renderer*/
			SDL_RenderCopy(renderer, cloud, &screen, &cloud1Rect);
			SDL_RenderCopy(renderer, cloud, &screen, &cloud2Rect);
			SDL_RenderCopy(renderer, cloud, &screen, &cloud3Rect);

			/*Adds grassMask To The Renderer*/
			SDL_RenderCopy(renderer, grassMask, &screen, &grassRect);


			/*Adds Next Round Indicator*/
			SDL_RenderCopy(renderer, nextRoundDisplay, NULL, &dispTxt);

			/*Shows The Rendered Image*/
			SDL_RenderPresent(renderer);

			/*Function To Move The Clouds*/
			cloud1Rect.x = ((gameTime - cloudT1) * -0.1 + 1300);
			cloud2Rect.x = ((gameTime - cloudT2) * 0.07) - 400;
			cloud3Rect.x = ((gameTime - cloudT3) * -0.09 + 1800);

			/*Cloud Position Resets*/
			/*Cloud 1*/
			if (cloud1Rect.x < -400)
			{
				cloud1Rect.x = 1600;
				cloudT1 = Timer();
			}

			/*Cloud 2*/
			if (cloud2Rect.x > 1300)
			{
				cloud2Rect.x = -300;
				cloudT2 = Timer();
			}

			/*Cloud 3*/
			if (cloud3Rect.x < -300)
			{
				cloud3Rect.x = 1600;
				cloudT3 = Timer();
			}
		}

		/*********************************************Next Round Check End******************************************************/

		/*******************************************Begin Round Init Stage******************************************************/
		if (roundInitFlag == true)
		{
			/*----------------------Round Indicator------------------*/
			/*Open Font*/
			TTF_Font* DHFont = TTF_OpenFont("duckhunt.ttf", 24);

			/*Create Color*/
			SDL_Color black = { 0, 0, 0 };

			/*Number to String*/
			strRound = ("Round " + (to_string(roundCount)));

			/*Create Round Number Surface*/
			roundNumber = TTF_RenderText_Solid(DHFont, strRound.c_str(), black);

			/*Create Round Number Texture*/
			roundNumberDisplay = SDL_CreateTextureFromSurface(renderer, roundNumber);


			/*Adds Round Indicator*/
			SDL_RenderCopy(renderer, roundNumberDisplay, NULL, &roundRect);

			/*Time When The Round Starts*/
			roundT1 = Timer();

			/*Free The Surface*/
			SDL_FreeSurface(roundNumber);

			/*------------------Score Indicator------------------------*/
			/*Open Font*/
			DHFonts = TTF_OpenFont("duckhunt.ttf", 12);

			/*Number to String*/
			strScore = ("Score: " + (to_string(score)));

			/*Create Round Number Surface*/
			newScore = TTF_RenderText_Solid(DHFonts, strScore.c_str(), black);

			/*Create Round Number Texture*/
			scoreDisplay = SDL_CreateTextureFromSurface(renderer, newScore);

			/*Adds Round Indicator*/
			SDL_RenderCopy(renderer, scoreDisplay, NULL, &dispScore);

			/*-------------------Ammo Indicator---------------------*/

			/*Create Round Number Surface*/
			ammo = TTF_RenderText_Solid(DHFonts, "Ammo: ", black);

			/*Create Round Number Texture*/
			ammoDisplay = SDL_CreateTextureFromSurface(renderer, ammo);

			/*Adds Round Indicator*/
			SDL_RenderCopy(renderer, ammoDisplay, NULL, &dispAmmo);

			/*Initialize The Round*/
			roundInit();
			gamePlay = true;
			roundInitFlag = false;
			quitRound = true;
			roundShow = true;
			roundStart = Timer();
		}
		
			/*********************************************End Round Init Stage*******************************************/

			/***********************************************Start Round Here*********************************************/
			if(quitRound)
			{
				if (currentDuck > 0)
				{
					inFlight = true;
					if (inFlight)
					{
						if (!roundShow)
						{
							/*Clears The Renderer*/
							SDL_RenderClear(renderer);

							/*Adds bgMask To The Renderer*/
							SDL_RenderCopy(renderer, bgMask, &screen, &bgRect);

							/*Adds All Clouds To The Renderer*/
							SDL_RenderCopy(renderer, cloud, &screen, &cloud1Rect);
							SDL_RenderCopy(renderer, cloud, &screen, &cloud2Rect);
							SDL_RenderCopy(renderer, cloud, &screen, &cloud3Rect);

							/*Function To Render The Ducks*/
							/*Renderer Ducks From Vector In Wings Up Or Down Position*/
							tmp = duckVec.at(currentDuck);

							//cout << tmp.x << " " << tmp.y << " " << currentDuck << endl;
							if (hitDuck == false)
							{
								if (forwardFlight == true)
								{
									if (wingPos == true)
									{
										SDL_RenderCopy(renderer, duckUp, &screen, &tmp);

									}
									else
									{
										SDL_RenderCopy(renderer, duckDown, &screen, &tmp);
									}
								}
								else
								{
									if (wingPos == true)
									{
										SDL_RenderCopy(renderer, duckUpB, &screen, &tmp);

									}
									else
									{
										SDL_RenderCopy(renderer, duckDownB, &screen, &tmp);
									}
								}
							}

							/*Adds grassMask To The Renderer*/
							SDL_RenderCopy(renderer, grassMask, &screen, &grassRect);

							UpdateScore();

							/*Render Bullets*/
							if (shots < 1)
							{
								SDL_RenderCopy(renderer, ammoTexture, NULL, &dispBul1);
							}
							if (shots < 2)
							{
								SDL_RenderCopy(renderer, ammoTexture, NULL, &dispBul2);
							}
							if (shots < 3)
							{
								SDL_RenderCopy(renderer, ammoTexture, NULL, &dispBul3);
							}

							/*Shows The Rendered Image*/
							SDL_RenderPresent(renderer);
						}
						

						/*Indicate Round*/
						if(roundShow)
						{
							/*Clears The Renderer*/
							SDL_RenderClear(renderer);

							/*Adds bgMask To The Renderer*/
							SDL_RenderCopy(renderer, bgMask, &screen, &bgRect);

							/*Adds All Clouds To The Renderer*/
							SDL_RenderCopy(renderer, cloud, &screen, &cloud1Rect);
							SDL_RenderCopy(renderer, cloud, &screen, &cloud2Rect);
							SDL_RenderCopy(renderer, cloud, &screen, &cloud3Rect);

							/*Adds grassMask To The Renderer*/
							SDL_RenderCopy(renderer, grassMask, &screen, &grassRect);

							/*Adds Round Indicator*/
							SDL_RenderCopy(renderer, roundNumberDisplay, &screen, &roundRect);

							/*Shows The Rendered Image*/
							SDL_RenderPresent(renderer);

							/*Function To Move The Clouds*/
							cloud1Rect.x = ((gameTime - cloudT1) * -0.1 + 1300);
							cloud2Rect.x = ((gameTime - cloudT2) * 0.07) - 400;
							cloud3Rect.x = ((gameTime - cloudT3) * -0.09 + 1800);

							/*Cloud Position Resets*/
							/*Cloud 1*/
							if (cloud1Rect.x < -400)
							{
								cloud1Rect.x = 1600;
								cloudT1 = Timer();
							}

							/*Cloud 2*/
							if (cloud2Rect.x > 1300)
							{
								cloud2Rect.x = -300;
								cloudT2 = Timer();
							}

							/*Cloud 3*/
							if (cloud3Rect.x < -300)
							{
								cloud3Rect.x = 1600;
								cloudT3 = Timer();
							}

							/*Moves Round Indicator*/
							roundRect.y = ((gameTime - roundT1) * -0.1 + 300);

							/*Stops Loop When Round Indicator Is Off Screen*/
							if (roundRect.y < (-150))
							{
								roundShow = false;
								shots = 0;
							}

						}
						else
						{
							/*Duck Position Resets*/

							cout << tmp.x << " " << tmp.y << " " << currentDuck << endl;

							/*Vertical Check*/
							if (tmp.y < -105)
							{
								currentDuck--;
								//cout << "sub " << currentDuck << tmp.y << endl;
								inFlight = false;
								forwardFlight = true;
								newDuck = true;
								hitDuck = true;
								duckT1 = roundTime;
							}

							/*Horizontal Check*/

							/*Right Wall*/
							if (tmp.x >= 1085)
							{
								if (forwardFlight == true)
								{
									duckT1xF = 0;
									duckSwitchx = tmp.x;
									forwardFlight = false;
								}
							}
							/*Left Wall*/

							if (tmp.x <= 0)
							{
								if (forwardFlight == false)
								{
									duckT1xF = roundTime;
									duckSwitchx = 0;
									forwardFlight = true;
								}
							}

							/*Move Objects*/

							/*Wing Counter, For Wing Position*/
							wingCount++;

							/*Sets Up Or Down Position*/
							if ((wingCount % 1000) == 0)
							{
								if (wingPos == true)
								{
									wingPos = false;
								}
								else
								{
									wingPos = true;
								}
							}

							/*Function To Move The Ducks*/
							if (hitDuck == false)
							{
								if (forwardFlight == true)
								{
									tmp.y = ((roundTime + duckT1) * duckSpeed + 800);
									tmp.x = ((roundTime - duckT1xF) * duckSpeedx + duckInitialx);
									duckVec[currentDuck] = tmp;
								}
								else
								{
									duckT1x = roundTime - duckT1xF;
									tmp.y = ((roundTime + duckT1) * duckSpeed + 800);
									tmp.x = ((roundTime - (2 * duckT1x)) * duckSpeedx + (duckSwitchx - duckInitialx) + 1085);
									duckVec[currentDuck] = tmp;
								}
							}
							
							if (newDuck == true)
							{
								/*Get Initial X Position*/
								duckT1xF = Timer();
								newDuckT = Timer();
								duckInitialx = tmp.x;
								hitDuck = false;
							}

							/*Reset newDuck So It Only Triggers When A New Duck Is Spawned*/
							newDuck = false;

							/*Function To Move The Clouds*/
							cloud1Rect.x = ((gameTime - cloudT1) * -0.1 + 1300);
							cloud2Rect.x = ((gameTime - cloudT2) * 0.07) - 400;
							cloud3Rect.x = ((gameTime - cloudT3) * -0.09 + 1800);

							//
							
							/*Cloud Position Resets*/
							/*Cloud 1*/
							if (cloud1Rect.x < -400)
							{
								cloud1Rect.x = 1600;
								cloudT1 = Timer();
							}

							/*Cloud 2*/
							if (cloud2Rect.x > 1300)
							{
								cloud2Rect.x = -300;
								cloudT2 = Timer();
							}

							/*Cloud 3*/
							if (cloud3Rect.x < -300)
							{
								cloud3Rect.x = 1600;
								cloudT3 = Timer();
							}
						}
						
					}
				}

				if (currentDuck <= 0)
				{
					quitRound = false;
					nextRound = true;
					roundCount++;
					gameContinue = true;
				}
			}

			/***********************************************End Round Here******************************************************/
	}
}

/*Initialize The Start Of Each Round*/
void roundInit()
{
	/*Start Round Sequence Music*/
	Mix_PlayMusic(roundTheme, 0);

	duckNum = 0;

	/*Set Wing Counter To 0*/
	wingCount = 0;

	if (roundCount < 8 && roundCount > 0)
	{
		/*Linear Progression For Duck Number, On Early Stages*/
		duckNum = 3 + roundCount;
		/*Slow Speed For Early Stages*/
		duckSpeed = -0.07;      //Vertical Speed
		duckSpeedx = 0.2;       //Horizontal Speed

	}
	else if(roundCount >= 8 && roundCount < 15)
	{
		/*Faster Ducks For Levels 8 Through 14*/
		duckNum = (5 + roundCount);
		duckSpeed = -0.085;
		duckSpeedx = .2;
	}
	else
	{
		/*Round 15 And On Is Max Speed*/
		duckNum = roundCount * 2;
		duckSpeed = -0.1;
		duckSpeedx = 0.2;
	}

	duckVec.resize(0);

	/*Fill Vector*/
	for(int i = 0; i < duckNum; i++)
	{
		/*Initial Y Position*/
		yStart = 675;

		/*Initial X Position*/
		xStart = rand() % 1080 + 200;

		/*Create New Duck*/
		insertDuck = {xStart - 195, yStart, 195, 105 };

		/*Add Duck To Existing Vector*/
		duckVec.push_back(insertDuck);
	}

	/*Starting Duck*/
	currentDuck = (duckVec.size() - 1);
}

void UpdateScore()
{

	/*Adds Round Indicator*/
	SDL_RenderCopy(renderer, scoreDisplay, NULL, &dispScore);

	/*Adds Round Indicator*/
	SDL_RenderCopy(renderer, ammoDisplay, NULL, &dispAmmo);

}

/*Initial Creation*/
bool CreateGame() 
{
	/*Checks For SDL Creation Errors*/
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		cout << "SDL Was Not Initialized" << SDL_GetError() << endl;
		return false;
	}

	/*Initialize TTF*/
	TTF_Init();

	/*Creates Window, Centered In The Middle Of The Screen*/
	window = SDL_CreateWindow("Duck Hunt",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_SHOWN);

	/*Checks For Window Creation Errors*/
	if (window == NULL) 
	{
		cout << "Window Was Not Created" << SDL_GetError() << endl;
		return false;
	}

	/*Creates Renderer*/
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		cout << "Error Creating The Renderer" << SDL_GetError() << endl;
		return false;
	}

	/*Creates Audio Mixer*/
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	/*Start Time Of The Game*/
	gameStart = SDL_GetTicks();

	return true;
}

/*Exit Function*/
void Close() 
{
	SDL_DestroyWindow(window);
	window = NULL;
	TTF_Quit();
	SDL_Quit();
}

SDL_Texture* LoadTexture(string file)
{

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(file.c_str());

	if (loadedSurface == NULL)
	{
		cout << "Unable To Load Image" << file.c_str() << IMG_GetError() << endl;
	}
	else 
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (newTexture == NULL)
		{
			cout << "Unable To Create Texture" << SDL_GetError() << endl;
		}

		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

void EventPoll()
{
	while (SDL_PollEvent(&event) != 0)
	{
		/*Checks For Quit Event*/
		if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
		{
			quitRound = false;
			quit = true;
		}

		/*Checks For Round Continue*/
		if (event.key.keysym.sym == SDLK_RETURN && gameContinue == true)
		{
			quitRound = false;
			roundInitFlag = true;
			roundSuccess = true;
			gameContinue = false;
			nextRound = false;
		}

		/*Checks For Game Start*/
		if (event.key.keysym.sym == SDLK_RETURN && gamePlay == false)
		{
			roundInitFlag = true;
			Mix_HaltMusic();
		}

		/*Check For Reload*/
		if (event.type == SDL_KEYUP && quitRound == true && roundShow == false)
		{
			if (event.key.keysym.sym == SDLK_r && shots > 0)
			{
				/*Reload Sound*/
				Mix_PlayMusic(reload, 0);

				shots = 0;
			}
		}

		/*Check For Mouse Click On The Duck*/
		if (event.type == SDL_MOUSEBUTTONUP && quitRound == true && roundShow == false)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				/*Register Shot*/
				shots++;

				/*Button Location*/
				Bx = event.button.x;
				By = event.button.y;

				/*Check Button Location With Duck Location*/
				if (shots <= 3)
				{

					if ((Bx > tmp.x) && (Bx < tmp.x + tmp.w) && (By > tmp.y) && (By < tmp.y + tmp.h))
					{
						/*Gunshot Noise*/
						Mix_PlayMusic(gunshot, 0);

						/*Position Set To Top Of Screen*/
						tmp.y = -150;
						tmp.x = 0;
						duckVec[currentDuck] = tmp;

						/*Duck Is Hit*/
						hitDuck = true;
						score += 100;

						/*Score Update*/
						/*Open Font*/
						DHFonts = TTF_OpenFont("duckhunt.ttf", 12);

						/*Number to String*/
						strScore = ("Score: " + (to_string(score)));

						/*Create Round Number Surface*/
						newScore = TTF_RenderText_Solid(DHFonts, strScore.c_str(), black);

						/*Create Round Number Texture*/
						scoreDisplay = SDL_CreateTextureFromSurface(renderer, newScore);

						/*Free The Surface*/
						SDL_FreeSurface(newScore);

						UpdateScore();
					}
					else
					{
						/*Gun Ricochet Noise*/
						Mix_PlayMusic(ricochet, 0);
					}
				}
				else
				{
					/*Gun Click Noise, No Ammo*/
					Mix_PlayMusic(click, 0);
				}
			}
		}
	}
}

Uint32 Timer()
{
	time = SDL_GetTicks() - gameStart;
	return time;
}