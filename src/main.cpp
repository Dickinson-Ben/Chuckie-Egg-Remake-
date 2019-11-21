using namespace std;
#include <iostream>
#include <vector>


// SDL - Simple DirectMedia Layer - https://www.libsdl.org/
#include "SDL.h" //Includes SDL in the same way
#include "SDL_image.h" //includes SDL in the same way
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <string>
#include <sstream>


int main(int argc, char *argv[]) {

	SDL_DisplayMode current;
	// SDL initialise and report errors if any
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s\n",
			SDL_GetError());
		return 1;
	}
	else
	{
		SDL_Log("SDL initialised OK!\n"); //reports success on
	}
	//display stuff
	for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i) { //cycles through the displays getting the resolution and refresh rate for each.

		int displayCheck = SDL_GetCurrentDisplayMode(0, &current);// assigns the number of displays found to a variable for error checking purposes

		if (displayCheck != 0)
			// Checks for errors and reports if display check returns a zero, meaning no displays were found.
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Could not get display mode for video display #%d: %s", i, SDL_GetError());

		else
			//prints the current number of displays and their resolitions (per loop itteration) to the console
			SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, current.w, current.h, current.refresh_rate);
	}




	//initilise variables 
	int spriteSizeX = 200;
	int spriteSizeY = 235;

	int eggSizeX = 145;
	int eggSizeY = 105;

	int seedSizeX = 122;
	int seedSizeY = 110;

	Uint32 delay = 10;

	int enemySizeY = 250;
	int enemySizeX = 160;
	int speed = 1;
	int speed2 = 1;
	int speed3 = 1;
	int speed4 = 1;
	int alphaVal;

	int gravity = 5;
	int jumpHeight = 50;
	int currentJump;
	int lastPlayerY;
	int playerSpeed = 5;
	int musicVolume = MIX_MAX_VOLUME; // the maximum is 128. 
	int score = 0;
	int timeRemaining = 800;
	unsigned int currentTime = 0;

	std::stringstream timeString;
	timeString << "Time: ";
	timeString << currentTime;

	std::stringstream scoreStream;
	scoreStream << "score: ";
	scoreStream << score;
	
	int lives = 4;

	std::stringstream livesStream;

	livesStream << "Lives: ";
	livesStream << lives;




	

	bool enemy1hitboundary;
	bool egg1collected = false;
	bool egg2collected = false;
	bool egg3collected = false;
	bool egg4collected = false;
	bool egg5collected = false;

	bool seed1collected = false;
	bool seed2collected = false;
	bool seed3collected = false;
	bool seed4collected = false;
	bool seed5collected = false;
	bool seed6collected = false;

	bool playMusic = true;
	bool deathLoop = false;

	bool paused = false;
	bool alive = true;
	bool movingRight = false;
	bool movingLeft = false;
	bool movingUp = false;
	bool movingDown = false;
	bool climbing = false;
	bool jumping = false;

	bool keyPrio = false;
	bool joyPrio = false;

	/*
		bool joyLeft = false;
		bool joyRight = false;
		bool joyUp = false;
		bool joyDown = false;*/


	SDL_Joystick *joy1;
	joy1 = SDL_JoystickOpen(0);


	//Initilising initial things
	SDL_Window *win = NULL;
	SDL_Renderer *renderer = NULL;

	//Initilise textures
	SDL_Texture *backgroundTexture;
	SDL_Texture *playerSprite;



	//Initilise Surface
	SDL_Surface *Loading_Surface;


	//REctabgles that will be used to select the image source (In shape and size on the sprite sheet) and the destination in the window
	SDL_Rect viewPort;

	SDL_Rect playerSource;
	SDL_Rect playerDestination;

	SDL_Rect scoreRect;
	SDL_Rect time;
	SDL_Rect livesRect;


	SDL_Rect scoreClip;

	SDL_Rect enemySource;
	SDL_Rect enemySource2;
	SDL_Rect enemySource3;
	SDL_Rect enemySource4;
	SDL_Rect enemyDestination;
	SDL_Rect enemyDestination2;
	SDL_Rect enemyDestination3;
	SDL_Rect enemyDestination4;
	SDL_Rect enemyDestination5;

	SDL_Rect seedSource;
	SDL_Rect seedDestination;
	SDL_Rect seedDestination2;
	SDL_Rect seedDestination3;
	SDL_Rect seedDestination4;
	SDL_Rect seedDestination5;
	SDL_Rect seedDestination6;

	SDL_Rect eggSource;
	SDL_Rect eggDestination;
	SDL_Rect eggDestination2;
	SDL_Rect eggDestination3;
	SDL_Rect eggDestination4;
	SDL_Rect eggDestination5;

	//ladder rects
	SDL_Rect ladder1;
	SDL_Rect ladder2;
	SDL_Rect ladder3;
	SDL_Rect ladder4;

	//platform rects
	SDL_Rect platformSource;
	SDL_Rect platform1;
	SDL_Rect platform2;
	SDL_Rect platform3;
	SDL_Rect platform4;
	SDL_Rect platform5;
	SDL_Rect platform6;
	SDL_Rect platform7;

	//Viewport parametres
	viewPort.x = 0;
	viewPort.y = 0;
	viewPort.w = 1920 / 2;
	viewPort.h = 1080 / 2;

	//player parametres
	playerSource.x = 0;
	playerSource.y = 0; //change these to select a different part of the sprite sheet
	playerSource.w = spriteSizeX;//change these to change the size of the sprite sample
	playerSource.h = spriteSizeY;


	playerDestination.x = 100;
	playerDestination.y = 455;
	playerDestination.w = spriteSizeX / 4;
	playerDestination.h = spriteSizeY / 4;

	//Ladder parametres 
	ladder1.x = 370;
	ladder1.y = 60;
	ladder1.w = 2;
	ladder1.h = 450;

	ladder2.x = 200;
	ladder2.y = 220;
	ladder2.w = 2;
	ladder2.h = 180;

	ladder3.x = 770;
	ladder3.y = 355;
	ladder3.w = 2;
	ladder3.h = 180;

	ladder4.x = 540;
	ladder4.y = 355;
	ladder4.w = 2;
	ladder4.h = 160;




	//platform rects


	platform1.x = -50;
	platform1.y = 220;
	platform1.w = 300;
	platform1.h = 1;

	platform2.x = 350;
	platform2.y = 60;
	platform2.w = 220;
	platform2.h = 1;

	platform3.x = 516;
	platform3.y = 175;
	platform3.w = 214;
	platform3.h = 1;

	platform4.x = 80;
	platform4.y = 400;
	platform4.w = 240;
	platform4.h = 1;

	platform5.x = 697;
	platform5.y = 270;
	platform5.w = 300;
	platform5.h = 1;

	platform6.x = 805;
	platform6.y = 435;
	platform6.w = 250;
	platform6.h = 1;

	platform7.x = 490;
	platform7.y = 355;
	platform7.w = 200;
	platform7.h = 1;

	//lives rect
	livesRect.x = 500;
	livesRect.y = 0;
	livesRect.w = 50;
	livesRect.h = 50;


	//score rect parametres
	scoreRect.x = 0;
	scoreRect.y = 0;
	scoreRect.w = 50;
	scoreRect.h = 50;

	time.x = 800;
	time.y = 0;
	time.w = 50;
	time.h = 50;



	//emeny source parameters
	enemySource.x = 10;
	enemySource.y = 235;
	enemySource.w = enemySizeX;
	enemySource.h = enemySizeY;

	enemySource2.x = 10;
	enemySource2.y = 235;
	enemySource2.w = enemySizeX;
	enemySource2.h = enemySizeY;

	enemySource3.x = 10;
	enemySource3.y = 235;
	enemySource3.w = enemySizeX;
	enemySource3.h = enemySizeY;

	enemySource4.x = 10;
	enemySource4.y = 235;
	enemySource4.w = enemySizeX;
	enemySource4.h = enemySizeY;

	//enemy destination parametres
	enemyDestination.x = 100;
	enemyDestination.y = 160;
	enemyDestination.w = enemySizeX / 4;
	enemyDestination.h = enemySizeY / 4;

	enemyDestination2.x = 300;
	enemyDestination2.y = 340;
	enemyDestination2.w = enemySizeX / 4;
	enemyDestination2.h = enemySizeY / 4;

	enemyDestination3.x = 500;
	enemyDestination3.y = 292;
	enemyDestination3.w = enemySizeX / 4;
	enemyDestination3.h = enemySizeY / 4;

	enemyDestination4.x = 800;
	enemyDestination4.y = 210;
	enemyDestination4.w = enemySizeX / 4;
	enemyDestination4.h = enemySizeY / 4;




	//egg parametres
	eggSource.x = 19;
	eggSource.y = 518;
	eggSource.w = eggSizeX;
	eggSource.h = eggSizeY;

	eggDestination.x = 500;
	eggDestination.y = 30;
	eggDestination.w = spriteSizeX / 6;
	eggDestination.h = spriteSizeY / 8;

	eggDestination2.x = 125;
	eggDestination2.y = 370;
	eggDestination2.w = spriteSizeX / 6;
	eggDestination2.h = spriteSizeY / 8;

	eggDestination3.x = 850;
	eggDestination3.y = 405;
	eggDestination3.w = spriteSizeX / 6;
	eggDestination3.h = spriteSizeY / 8;

	eggDestination4.x = 700;
	eggDestination4.y = 148;
	eggDestination4.w = spriteSizeX / 6;
	eggDestination4.h = spriteSizeY / 8;

	eggDestination5.x = 125;
	eggDestination5.y = 190;
	eggDestination5.w = spriteSizeX / 6;
	eggDestination5.h = spriteSizeY / 8;

	//seed parametres
	seedSource.x = 23;
	seedSource.y = 638;
	seedSource.w = seedSizeX;
	seedSource.h = seedSizeY;

	seedDestination.x = 20;
	seedDestination.y = 190;
	seedDestination.w = spriteSizeX / 6;
	seedDestination.h = spriteSizeY / 7;

	seedDestination2.x = 400;
	seedDestination2.y = 30;
	seedDestination2.w = spriteSizeX / 6;
	seedDestination2.h = spriteSizeY / 7;

	seedDestination3.x = 600;
	seedDestination3.y = 142;
	seedDestination3.w = spriteSizeX / 6;
	seedDestination3.h = spriteSizeY / 7;

	seedDestination4.x = 800;
	seedDestination4.y = 235;
	seedDestination4.w = spriteSizeX / 6;
	seedDestination4.h = spriteSizeY / 7;

	seedDestination5.x = 900;
	seedDestination5.y = 405;
	seedDestination5.w = spriteSizeX / 6;
	seedDestination5.h = spriteSizeY / 7;

	seedDestination6.x = 600;
	seedDestination6.y = 320;
	seedDestination6.w = spriteSizeX / 6;
	seedDestination6.h = spriteSizeY / 7;

	//Initialise mixer - Shouldn't need since all is initilised
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_mixer init error: %s\n   PERHAPS NO HEADPHONES/SPEAKERS CONNECTED\n", Mix_GetError());
		return 1;
	}
	SDL_Log("SDL_mixer initialised OK!\n");


	win = SDL_CreateWindow("Ben Dickinson | CGP2011M Games Programming | DIC11213186", current.w / 4, current.h / 4, current.w / 2, current.h / 2, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
	//window creation error checking
	if (win == nullptr)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_CreateWindow init error: %s\n", SDL_GetError());
		return 1;
	}
	else
	{
		SDL_Log("Window created!\n");
	}

	//Renderer

	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_CreateRenderer init error: %s\n", SDL_GetError());
		return 1;
	}
	else
	{
		SDL_Log("Renderer created!\n");
	}

	SDL_RenderSetLogicalSize(renderer, viewPort.w, viewPort.h);

	//viewport
	SDL_RenderSetViewport(renderer, &viewPort);

	//render scaling 



	//SDL_RenderSetScale(renderer, , ); uses the renderer and a float for x and a float for y

	//font etc. for on screen displays
	TTF_Init();
	TTF_Font *gameFont = TTF_OpenFont("bin/assets/OpenSans-Bold.ttf", 24); //opens the desired font and font size. 

	if (gameFont == NULL)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_TTF init error: %s\n   Font failed to load: %d \n", SDL_GetError());
		return 1;
	}
	else
	{
		SDL_Log("Font loaded ok!\n");
	}
	SDL_Color gameFontColour = { 255,255,255 }; //Initialises the colour variable and sets it to white using the RGB values in {}



	SDL_Surface *timeSurface = TTF_RenderText_Solid(gameFont, timeString.str().c_str(), gameFontColour);
	SDL_Texture *timeTexture = SDL_CreateTextureFromSurface(renderer, timeSurface);
	if (timeSurface != NULL && timeTexture != NULL)
		if (timeSurface == NULL || timeTexture == NULL)
		{
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
				"Error loading the time surface / texture: %d \n", SDL_GetError());
			return 1;
		}
		else
		{
			SDL_Log("Time surface / texture loaded ok!\n");
		}
	SDL_FreeSurface(timeSurface);

	SDL_Surface *scoreSurface = TTF_RenderText_Solid(gameFont, scoreStream.str().c_str(), gameFontColour);
	SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
	SDL_FreeSurface(scoreSurface);

	SDL_Surface *livesSurface = TTF_RenderText_Solid(gameFont, livesStream.str().c_str(), gameFontColour);
	SDL_Texture *livesTexture = SDL_CreateTextureFromSurface(renderer, livesSurface);
	//SDL_FreeSurface(scoreSurface);


	//Load the music
	Mix_Music *music = Mix_LoadMUS("bin/assets/Chiptune_Does_Dubstep.wav");
	if (music == NULL)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_TTF init error: %s\n   Font failed to load: %d \n", SDL_GetError());
		return 1;
	}
	else
	{
		SDL_Log("Font loaded ok!\n");
	}

	Mix_PlayMusic(music, -0); //change to -1 to play through on loop. Leave outside game loop in order to 

	//Load the sound effect
	Mix_Chunk *collectEgg = Mix_LoadWAV("bin/assets/Pickup_Egg.wav");
	if (collectEgg == NULL)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_Mix_Chunk init error: %s\n   collectEgg failed to load: %d \n", SDL_GetError());
		return 1;
	}
	else
	{
		SDL_Log("collectEgg loaded ok!\n");
	}


	Mix_Chunk *jump = Mix_LoadWAV("bin/assets/Jump.wav");
	if (jump == NULL)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_Mix_Chunk init error: %s\n   jump failed to load: %d \n", SDL_GetError());
		return 1;
	}
	else
	{
		SDL_Log("jump loaded ok!\n");
	}

	Mix_Chunk *collectSeed = Mix_LoadWAV("bin/assets/Pickup_Seed2.wav");
	if (collectSeed == NULL)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_Mix_Chunk init error: %s\n   collectSeed failed to load: %d \n", SDL_GetError());
		return 1;
	}
	else
	{
		SDL_Log("collectSeed loaded ok!\n");
	}

	Mix_Chunk *hit = Mix_LoadWAV("bin/assets/Hit_Hurt.wav");
	if (hit == NULL)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_Mix_Chunk init error: %s\n   hit failed to load: %d \n", SDL_GetError());
		return 1;
	}
	else
	{
		SDL_Log("hit loaded ok!\n");
	}

	Mix_Chunk *walk = Mix_LoadWAV("bin/assets/WalkCycle2.wav");
	if (walk == NULL)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_Mix_Chunk init error: %s\n   walk failed to load: %d \n", SDL_GetError());
		return 1;
	}
	else
	{
		SDL_Log("walk loaded ok!\n");
	}

	//Image Loading

	//Background
	Loading_Surface = IMG_Load("bin/assets/Chuckie Egg Background.BMP");
	if (Loading_Surface == NULL)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_IMG_Load init error: %s\n   Loading_Surface failed to load: %d \n", SDL_GetError());
		return 1;
	}
	else
	{
		SDL_Log("Loading_Surface loaded ok!\n");
	}

	backgroundTexture = SDL_CreateTextureFromSurface(renderer, Loading_Surface);
	if (backgroundTexture == NULL)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_CreateTextureFromSurface init error: %s\n   backgroundTexture failed to load: %d \n", SDL_GetError());
		return 1;
	}
	else
	{
		SDL_Log("backgroundTexture loaded ok!\n");
	}

	SDL_FreeSurface(Loading_Surface);

	//temporary surface for platforms for debugging 
	SDL_Surface *tempSurface = IMG_Load("bin/assets/Chuckie Egg Start Screen.png");
	SDL_Texture *tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	platformSource.x = 0;
	platformSource.y = 0;
	platformSource.w = NULL;
	platformSource.h = NULL;

	//sprite sheet
	Loading_Surface = IMG_Load("bin/assets/Chuckie Egg Sprite Sheet.PNG");
	if (Loading_Surface == NULL)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"IMG_Load init error: %s\n   Loading_Surface Chuckie Egg Sprite Sheet failed to load: %d \n", SDL_GetError());
		return 1;
	}
	else
	{
		SDL_Log("backgroundTexture loaded ok!\n");
	}

	playerSprite = SDL_CreateTextureFromSurface(renderer, Loading_Surface);

	if (playerSprite == NULL)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"IMG_Load init error: %s\n   playerSprite failed to load: %d \n", SDL_GetError());
		return 1;
	}
	else
	{
		SDL_Log("playerSprite loaded ok!\n");
		SDL_FreeSurface(Loading_Surface);
	}



	SDL_Event event;//initialises SDL_Event as an event I guess?
	bool runGame = true; //boolean value used as loop condition
	bool pause = false;
	bool fullScreen = false;
	unsigned int lastTime = 0;  //sets up variables for time tracking
	unsigned int lastTime2 = 0, currentTime2 = SDL_GetTicks();
	unsigned int lastTime3 = 0, currentTime3 = SDL_GetTicks();
	unsigned int lastTime4 = 0, currentTime4 = SDL_GetTicks();
	unsigned int lastTime5 = 0, currentTime5 = SDL_GetTicks();
	int WIDTH, HEIGHT; //created variables width and height for use in the game loop / window resizing
	bool splashScreen = true;

	int tempAlpha = 0;
	//************************************************************************

	////either do another while loop or do two if's withing the main while loop 
	while (splashScreen)
	{


		SDL_RenderCopy(renderer, tempTexture, NULL, NULL);

		SDL_RenderPresent(renderer);
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_RETURN: splashScreen = false;
					break;
				case SDLK_ESCAPE: splashScreen = false;
					runGame = false;
				}
			}
		}
	}

	while (runGame)//Start game loop - check if game should end
	{


		if (lives == 0)
		{
			runGame = false;
		}
		if (timeRemaining == 0)
		{
			runGame = false;
		}

		//Render background 
		SDL_RenderCopy(renderer, backgroundTexture, NULL, &viewPort);

		//render time to screen
		SDL_Surface *timeSurface = TTF_RenderText_Solid(gameFont, timeString.str().c_str(), gameFontColour);
		SDL_Texture *timeTexture = SDL_CreateTextureFromSurface(renderer, timeSurface);
		SDL_RenderCopy(renderer, timeTexture, NULL, &time);

		//texture needs to be re-created when the score updates, could possible be put into collision detection?
		SDL_Surface *scoreSurface = TTF_RenderText_Solid(gameFont, scoreStream.str().c_str(), gameFontColour);
		SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
		SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);


		SDL_Surface *livesSurface = TTF_RenderText_Solid(gameFont, livesStream.str().c_str(), gameFontColour);
		SDL_Texture *livesTexture = SDL_CreateTextureFromSurface(renderer, livesSurface);
		SDL_RenderCopy(renderer, livesTexture, NULL, &livesRect);


		//	time update code 
		currentTime = SDL_GetTicks();
		if (paused != true)
		{
			if (currentTime > lastTime + 1000) //checks to see if 1000 miliseconds (1 second) has passed
			{
				lastTime = lastTime / 1000; //divides the last time variable by 1000 to print seconds as opposed to miliseconds to the console (easier to read)
				//strig clear and addittion
				timeRemaining -= 1;
				timeString.str("");


				timeString << "Time: ";
				timeString << timeRemaining;
				lastTime = currentTime;//updates currentTime to the current number of miliseconds passed at that point, enabling it to properly keep track
			}
		}


		//platform boxes, textures are temporary
		SDL_RenderCopy(renderer, NULL, NULL, &platform1); //putting NULL in both spaces renderes no texture but leaves you with the rect! 
		SDL_RenderCopy(renderer, NULL, NULL, &platform2);
		SDL_RenderCopy(renderer, NULL, NULL, &platform3);
		SDL_RenderCopy(renderer, NULL, NULL, &platform4);
		SDL_RenderCopy(renderer, NULL, NULL, &platform5);
		SDL_RenderCopy(renderer, NULL, NULL, &platform6);
		SDL_RenderCopy(renderer, NULL, NULL, &platform7);

		//ladders
		SDL_RenderCopy(renderer, NULL, NULL, &ladder1);
		SDL_RenderCopy(renderer, NULL, NULL, &ladder2);
		SDL_RenderCopy(renderer, NULL, NULL, &ladder3);
		SDL_RenderCopy(renderer, NULL, NULL, &ladder4);



		//render player 
		if (alive == true)
		{
			SDL_RenderCopy(renderer, playerSprite, &playerSource, &playerDestination);
		}


		//render enemies
		SDL_RenderCopy(renderer, playerSprite, &enemySource, &enemyDestination);
		SDL_RenderCopy(renderer, playerSprite, &enemySource2, &enemyDestination2);
		SDL_RenderCopy(renderer, playerSprite, &enemySource3, &enemyDestination3);
		SDL_RenderCopy(renderer, playerSprite, &enemySource4, &enemyDestination4);


		//render Seeds if not collected
		if (seed1collected != true)
		{
			SDL_RenderCopy(renderer, playerSprite, &seedSource, &seedDestination);
		}
		if (seed2collected != true)
		{
			SDL_RenderCopy(renderer, playerSprite, &seedSource, &seedDestination2);
		}
		if (seed3collected != true)
		{
			SDL_RenderCopy(renderer, playerSprite, &seedSource, &seedDestination3);
		}
		if (seed4collected != true)
		{
			SDL_RenderCopy(renderer, playerSprite, &seedSource, &seedDestination4);
		}
		if (seed5collected != true)
		{
			SDL_RenderCopy(renderer, playerSprite, &seedSource, &seedDestination5);
		}
		if (seed6collected != true)
		{
			SDL_RenderCopy(renderer, playerSprite, &seedSource, &seedDestination6);
		}



		//seed collission and score addition
		if (SDL_HasIntersection(&playerDestination, &seedDestination))
		{

			if (seed1collected == false)
			{
				Mix_PlayChannel(-1, collectSeed, 0);
				score += 50;
				scoreStream.str("");
				scoreStream << "Score: ";
				scoreStream << score;
				printf("seed 1 collected\n");
				//printf("%d\n", score);
				seed1collected = true;
			}
		}
		if (SDL_HasIntersection(&playerDestination, &seedDestination2))
		{


			if (seed2collected == false)
			{
				Mix_PlayChannel(-1, collectSeed, 0);
				score += 50;
				scoreStream.str("");
				scoreStream << "Score: ";
				scoreStream << score;
				printf("seed 2 collected\n");
				//printf("%d\n", score);
				seed2collected = true;
			}
		}
		if (SDL_HasIntersection(&playerDestination, &seedDestination3))
		{

			if (seed3collected == false)
			{
				score += 50;
				scoreStream.str("");
				scoreStream << "Score: ";
				scoreStream << score;
				Mix_PlayChannel(-1, collectSeed, 0);
				printf("seed 3 collected\n");
				//printf("%d\n", score);
				seed3collected = true;
			}
		}

		if (SDL_HasIntersection(&playerDestination, &seedDestination4))
		{
			if (seed4collected == false)
			{
				Mix_PlayChannel(-1, collectSeed, 0);
				score += 50;
				scoreStream.str("");
				scoreStream << "Score: ";
				scoreStream << score;
				printf("seed 4 collected\n");
				//printf("%d\n", score);
				seed4collected = true;
			}
		}
		if (SDL_HasIntersection(&playerDestination, &seedDestination5))
		{

			if (seed5collected == false)
			{
				Mix_PlayChannel(-1, collectSeed, 0);
				score += 50;
				scoreStream.str("");
				
				scoreStream << "Score: ";
				scoreStream << score;
				printf("seed 5 collected\n");
				//printf("%d\n", score);
				seed5collected = true;
			}
		}
		if (SDL_HasIntersection(&playerDestination, &seedDestination6))
		{
			if (seed6collected == false)
			{

				score += 50;
				scoreStream.str("");
				scoreStream << "Score: ";
				scoreStream << score;
				Mix_PlayChannel(-1, collectSeed, 0);
				printf("seed 6 collected\n");
				//printf("%d\n", score);
				seed6collected = true;
			}
		}



		//render eggs if not collected
		if (egg1collected != true)
		{
			SDL_RenderCopy(renderer, playerSprite, &eggSource, &eggDestination);
		}

		if (egg2collected != true)
		{
			SDL_RenderCopy(renderer, playerSprite, &eggSource, &eggDestination2);
		}

		if (egg3collected != true)
		{
			SDL_RenderCopy(renderer, playerSprite, &eggSource, &eggDestination3);
		}

		if (egg4collected != true)
		{
			SDL_RenderCopy(renderer, playerSprite, &eggSource, &eggDestination4);
		}

		if (egg5collected != true)
		{
			SDL_RenderCopy(renderer, playerSprite, &eggSource, &eggDestination5);
		}


		//egg collection / score addition
		if (SDL_HasIntersection(&playerDestination, &eggDestination))
		{


			if (egg1collected == false)
			{
				Mix_PlayChannel(-1, collectEgg, 0);
				score += 100;
				scoreStream.str("");
				scoreStream << "Score: ";
				scoreStream << score;
				//printf("%d\n", score);
				egg1collected = true;
			}
		}

		if (SDL_HasIntersection(&playerDestination, &eggDestination2))
		{


			if (egg2collected == false)
			{
				Mix_PlayChannel(-1, collectEgg, 0);
				score += 100;
				scoreStream.str("");
				scoreStream << "Score: ";
				scoreStream << score;
				//printf("%d\n", score);
				egg2collected = true;
			}
		}
		if (SDL_HasIntersection(&playerDestination, &eggDestination3))
		{


			if (egg3collected == false)
			{
				Mix_PlayChannel(-1, collectEgg, 0);
				score += 100;
				scoreStream.str("");
				scoreStream << "Score: ";
				scoreStream << score;
				//printf("%d\n", score);
				egg3collected = true;

			}
		}
		if (SDL_HasIntersection(&playerDestination, &eggDestination4))
		{


			if (egg4collected == false)
			{
				Mix_PlayChannel(-1, collectEgg, 0);
				score += 100;
				scoreStream.str("");
				scoreStream << "Score: ";
				scoreStream << score;
			//	printf("%d\n", score);
				egg4collected = true;

			}
		}
		if (SDL_HasIntersection(&playerDestination, &eggDestination5))
		{


			if (egg5collected == false)
			{
				Mix_PlayChannel(-1, collectEgg, 0);
				score += 100;
				scoreStream.str("");
				scoreStream << "Score: ";
				scoreStream << score;
				//printf("%d\n", score);
				egg5collected = true;

			}
		}

		//enemy collision detection
		if (SDL_HasIntersection(&playerDestination, &enemyDestination))
		{
			lives -= 1;
			livesStream.str("");
			livesStream << "Lives: ";
			livesStream << lives;
			SDL_Log("Collided with enemy, Life lost! lives remaining: %d", lives);
			Mix_PlayChannel(-1, hit, 0);
			SDL_Delay(1000);
			//alive = false;
			playerDestination.x = 100;
			playerDestination.y = 450;


		}

		if (SDL_HasIntersection(&playerDestination, &enemyDestination2))
		{
			lives -= 1;
			livesStream.str("");
			livesStream << "Lives: ";
			livesStream << lives;
			Mix_PlayChannel(-1, hit, 0);
			SDL_Delay(1000);
			//alive = false;
			playerDestination.x = 100;
			playerDestination.y = 450;
			SDL_Log("Collided with enemy, Life lost! lives remaining: %d", lives);


		}

		if (SDL_HasIntersection(&playerDestination, &enemyDestination3))
		{
			lives -= 1;
			livesStream.str("");
			livesStream << "Lives: ";
			livesStream << lives;
			Mix_PlayChannel(-1, hit, 0);
			SDL_Delay(1000);
			//alive = false;
			playerDestination.x = 100;
			playerDestination.y = 450;
			SDL_Log("Collided with enemy, Life lost! lives remaining: %d", lives);

		}

		if (SDL_HasIntersection(&playerDestination, &enemyDestination4))
		{
			lives -= 1;
			livesStream.str("");
			livesStream << "Lives: ";
			livesStream << lives;
			Mix_PlayChannel(-1, hit, 0);
			SDL_Delay(1000);
			//alive = false;
			playerDestination.x = 100;
			playerDestination.y = 450;
			SDL_Log("Collided with enemy, Life lost! lives remaining: %d", lives);


		}
#pragma region Moving
		SDL_RenderPresent(renderer);

		if (paused == false)
		{

			{
				enemyDestination.x -= speed;
				//		lastTime2 = currentTime2;
				if (enemyDestination.x < 0)
				{
					speed = -1;
					enemySource.x = 460;
				}
				if (enemyDestination.x > 200)
				{
					speed = 1;
					enemySource.x = 10;
				}
			}

			//enemy 2 movement
		//	currentTime3 = SDL_GetTicks();
		//	if (currentTime3 > lastTime3 + 500)

			enemyDestination2.x -= speed2;
			//		lastTime3 = currentTime3;
			if (enemyDestination2.x < 100)
			{
				speed2 = -1;
				//Sprite switch code goes here
				enemySource2.x = 460;
			}
			if (enemyDestination2.x > 305)
			{
				speed2 = 1;
				//sprite switch code goes here
				enemySource2.x = 10;
			}




			enemyDestination3.x -= speed3;
			if (enemyDestination3.x < 490)
			{
				speed3 = -1;
				enemySource3.x = 460;
			}
			if (enemyDestination3.x > 700)
			{
				speed3 = 1;
				enemySource3.x = 10;
			}


			//enemy 4 movement


			enemyDestination4.x -= speed4;
			//currentTime3 = SDL_GetTicks();
			if (enemyDestination4.x < 690)
			{
				speed4 = -1;
				enemySource4.x = 460;

			}
			if (enemyDestination4.x > 900)
			{
				speed4 = 1;
				enemySource4.x = 10;
			}







			//fall if player is above floor
			if (playerDestination.y < 456)
			{
				if (climbing == false)
				{
					playerDestination.y += gravity;
				}
			}

			//checks for collissionson platforms and ladders!
			if (SDL_HasIntersection(&playerDestination, &platform1) || SDL_HasIntersection(&playerDestination, &platform2) || SDL_HasIntersection(&playerDestination, &platform3)
				|| SDL_HasIntersection(&playerDestination, &platform4) || SDL_HasIntersection(&playerDestination, &platform5) || SDL_HasIntersection(&playerDestination, &platform6)
				|| SDL_HasIntersection(&playerDestination, &platform7) || SDL_HasIntersection(&playerDestination, &ladder1) || SDL_HasIntersection(&playerDestination, &ladder2)
				|| SDL_HasIntersection(&playerDestination, &ladder3) || SDL_HasIntersection(&playerDestination, &ladder4))
			{
				climbing = true;
			}
			else
			{
				climbing = false;
			}


			//movement code for player moving to avoid using key repeat
			if (movingRight != false)
			{
				if (playerDestination.x <= 920)
				{

					playerDestination.x += playerSpeed;
					currentTime2 = SDL_GetTicks();
					if (currentTime2 > lastTime2 + 100)
					{
						playerSource.x = 521;
						Mix_PlayChannel(-1, walk, 0);
					}
					if (currentTime2 > lastTime2 + 200)
					{
						playerSource.x = 356;
						lastTime2 = currentTime2;
						Mix_PlayChannel(-1, walk, 0);
					}
				}

			}

			if (movingLeft != false)
			{
				if (playerDestination.x >= 0)
				{

					playerDestination.x -= playerSpeed;

					currentTime2 = SDL_GetTicks();
					if (currentTime2 > lastTime2 + 100)
					{
						playerSource.x = 10;
						Mix_PlayChannel(-1, walk, 0);
					}
					if (currentTime2 > lastTime2 + 200)
					{
						playerSource.x = 186;
						lastTime2 = currentTime2;
						Mix_PlayChannel(-1, walk, 0);
					}
				}
			}

			if (movingUp == true)
			{
				
					playerDestination.y -= playerSpeed;
					currentTime2 = SDL_GetTicks();
					if (currentTime2 > lastTime2 + 100)
					{
						playerSource.x = 706;
					}
					if (currentTime2 > lastTime2 + 200)
					{
						playerSource.x = 850;
						lastTime2 = currentTime2;
					}
				}
			

			if (movingDown != false)
			{
				
				
					playerDestination.y += playerSpeed;
					currentTime2 = SDL_GetTicks();
					if (currentTime2 > lastTime2 + 100)
					{
						playerSource.x = 706;
					}
					if (currentTime2 > lastTime2 + 200)
					{
						playerSource.x = 850;
						lastTime2 = currentTime2;
					}
				

			}

			if (jumping == true)
			{
				//gravity = 0;
				climbing = true;
				movingUp = true;

				if (lastPlayerY - playerDestination.y >= jumpHeight)
				{
					SDL_Log("Paused\n");
					movingUp = false;
					climbing = false;
					jumping = false;
					keyPrio = false; 
				}
			}




		}//end of if
		if (SDL_PollEvent(&event))
		{

			//keyboard input
			if (event.type == SDL_KEYDOWN && !event.key.repeat)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE: runGame = false;	 //sets rungame to false if escape is pressed	  
					break;
				case SDLK_w:
					keyPrio = true;
					if (SDL_HasIntersection(&playerDestination, &ladder1) || SDL_HasIntersection(&playerDestination, &ladder2)
						|| SDL_HasIntersection(&playerDestination, &ladder3) || SDL_HasIntersection(&playerDestination, &ladder4))
					{

						movingUp = true;
						climbing = true;
					}

					break;
				case SDLK_s:
					keyPrio = true;
					if (SDL_HasIntersection(&playerDestination, &ladder1) || SDL_HasIntersection(&playerDestination, &ladder2)
						|| SDL_HasIntersection(&playerDestination, &ladder3) || SDL_HasIntersection(&playerDestination, &ladder4))
					{
						movingDown = true;
						climbing = true;
					}
					break;

				case SDLK_p:
					if (paused == false)
					{
						paused = true;
						Mix_PauseMusic();
						SDL_Log("Paused\n");
					}
					else
					{
						Mix_ResumeMusic();
						paused = false;
					}
					break;


				case SDLK_a:
					keyPrio = true;
					movingLeft = true;
					break;
				case SDLK_d:
					keyPrio = true;
					movingRight = true;
					break;

				case SDLK_SPACE:
					//climbing = true;

					lastPlayerY = playerDestination.y;
					keyPrio = true;
					jumping = true;
					Mix_PlayChannel(-1, jump, 0);
					playerSource.x = 365;
					break;

				case SDLK_KP_PLUS: if (fullScreen == false)
				{
					SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);
					SDL_GetCurrentDisplayMode(0, &current);//gets the resolution for the main display and sets them to current.w and current.h (These are inbuilt values)
					WIDTH = current.w; //assign current.w and h to width and hight since they apparently can't be passed in directly
					HEIGHT = current.h;
					fullScreen = true;
				}
								   break;

				case SDLK_KP_MINUS: if (fullScreen = true)
				{
					SDL_SetWindowFullscreen(win, 0); //setting the full screen parameter to 0 disables full screen mode!
					SDL_GetCurrentDisplayMode(0, &current);
					WIDTH = current.w;
					HEIGHT = current.h;
					fullScreen = false;
				}
									break;
				case SDLK_END:
					if (playMusic == true)
					{
						Mix_PauseMusic();
						playMusic = false;
					}
					else
					{
						Mix_ResumeMusic();
						playMusic = true;
					}
					break;
				case SDLK_UP:
					if (musicVolume != 128)
					{
						Mix_VolumeMusic(musicVolume += 8);
						Mix_VolumeChunk(collectEgg, musicVolume);
						Mix_VolumeChunk(collectSeed, musicVolume);
						Mix_VolumeChunk(jump, musicVolume);
						Mix_VolumeChunk(hit, musicVolume);
						Mix_VolumeChunk(walk, musicVolume);
						SDL_Log("Volume increased by 8 volume is now at %d\n", musicVolume);
					}
					break;

				case SDLK_DOWN:
					if (musicVolume != 0)
					{
						Mix_VolumeMusic(musicVolume -= 8);
						Mix_VolumeChunk(collectEgg, musicVolume);
						Mix_VolumeChunk(collectSeed , musicVolume);
						Mix_VolumeChunk(jump, musicVolume );
						Mix_VolumeChunk(hit, musicVolume);
						Mix_VolumeChunk(walk, musicVolume);

						SDL_Log("Volume decreased by 8 volume is now at %d\n", musicVolume);

					}
					break;
				case SDLK_LSHIFT: playerSpeed = 7;
					break;
				}
			}

			//key UP for key release things!
			if (event.type == SDL_KEYUP)// && !event.key.repeat)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_LSHIFT: playerSpeed = 3;
					break;
				case SDLK_d:
					keyPrio = false;
					movingRight = false;
					//	climbing = false;
					break;
				case SDLK_a:
					keyPrio = false;
					movingLeft = false;
					//	climbing = false;
					break;
				case SDLK_w:
					keyPrio = false;
					movingUp = false;
					climbing = false;
					break;
				case SDLK_s:
					keyPrio = false;
					movingDown = false;

					break;
				case SDLK_SPACE:
					climbing = false;
					//keyPrio = false;
					//jumping = false;
					break;

				}
			}
		}

#pragma endregion


		//uses the quit button on the SDL window to end the applicaiton
		if (event.type == SDL_QUIT)
		{
			runGame = false;
		}


		//window resizing stuff. Pass in monitor resolution for full screen and window resolution for resizing

		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
			SDL_GetCurrentDisplayMode(0, &current);
			WIDTH = current.w; //assign current.w and h to width and hight since they apparently can't be passed in directly
			HEIGHT = current.h;
			SDL_Log("Window Maximized");

		}


		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
			SDL_GetCurrentDisplayMode(0, &current);//gets the resolution for the main display and sets them to current.w and 
			SDL_GetWindowSize(win, &WIDTH, &HEIGHT);
			SDL_Log("Window Resized");

		}


		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESTORED) {
			SDL_GetCurrentDisplayMode(0, &current);//gets the resolution for the main display and sets them to current.w and 
			SDL_GetWindowSize(win, &WIDTH, &HEIGHT);
			SDL_Log("Window Restored");

		}



		//std::cout << "Loop complete " << std::endl; 
		SDL_Delay(delay);
	}

	// Clean up! Disposes of textures and such
	SDL_Log("Finished. Cleaning up and closing down\n");
	SDL_DestroyTexture(playerSprite);
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	TTF_CloseFont(gameFont);

	//Do wait code here
	//SDL_Delay(2000);
	//closes the window 

	SDL_Quit();
	return 0;
}
