#include "Game.h"
#include "Game_Base.h"
#include "Game_Utils.h"
#include "LTexture.h"
#include "Button.h"
#include "Player.h"
#include "Object.h"
#include "Background.h"
#include "TextManager.h"
#include "CollisionManager.h"
#include <vector>
using namespace std;
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Color textColor = { 255,255,255,0 };
TTF_Font* gFont = nullptr;
Mix_Music* gMusic = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClick = nullptr;
Mix_Chunk* gEat = nullptr;
Mix_Chunk* gJump = nullptr;
Mix_Chunk* gLose = nullptr;
const std::string SCENCE1[BACKGROUND_LAYER] = {
	"Img/background/scence1.png",
	"Img/background/scence2.png",
	"Img/background/scence3.png",
	"Img/background/scence4.png",
	"Img/background/scence5.png",
	"Img/background/scence6.png",
	"Img/background/scence7.png",
	"Img/background/scence8.png",
	"Img/background/scence9.png",
};
Player p;
Background Pipe_Above1;
Background Pipe_Below1;
Background Pipe_Above2;
Background Pipe_Below2;
Background Pipe_Above3;
Background Pipe_Below3;
Background Fruit;
SDL_Rect gFruitClips[TOTAL_FOOD];
SDL_Rect gBoomClips[BOOM_FRAME];
Background Boom;
TextManager score;
TextManager death;
TextManager gameover;
TextManager press;
TextManager high;
TextManager timer[3];
int frame_Type[3]={0};
int points = 0;
int deathcount = 0;
int best=0;
int highscore;
int variance1 = rand() % 201 - 100;
int variance2 = rand() % 201 - 100;
int variance3 = rand() % 201 - 100;
int variance4 = rand() % 201 - 100;
int variance5 = rand() % 522;
int type=(variance1+100) % TOTAL_FOOD;
bool Die = false;
bool boom=false;
int frame_Character = 0;
int frame_Pipe=0;
int OffsetSpeed_Ground = BASE_OFFSET_SPEED;
int last=1;
std::vector <double> OffsetSpeed_Bkgr(BACKGROUND_LAYER, BASE_OFFSET_SPEED);

SDL_Rect gPlayButton[BUTTON_TOTAL];
SDL_Rect gHelpButton[BUTTON_TOTAL];
SDL_Rect gExitButton[BUTTON_TOTAL];
SDL_Rect gBackButton[BUTTON_TOTAL];
SDL_Rect gSoundButton[BUTTON_TOTAL];
SDL_Rect gInfoButton[BUTTON_TOTAL];
SDL_Rect gCharacterClips[FLYING_FRAMES];
LTexture gMenuTexture;
LTexture gInstructionTexture;
LTexture g_BackgroundTexture[BACKGROUND_LAYER];
LTexture gPlayButtonTexture;
LTexture gExitButtonTexture;
LTexture gBackButtonTexture;
LTexture gSoundButtonTexture;
LTexture gInfoButtonTexture;
Button PlayButton(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
Button SoundButton(700, 12);
Button InfoButton(HELP_BUTTON_POSX, HELP_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button BackButton(BACK_BUTTON_POSX, BACK_BUTTON_POSY);

bool Game::Init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO ) < 0)
	{
		printf("Can not initialize SDL.: %s\n", SDL_GetError());
		success = false;
	}

	else
	{
		SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
            std::cout << "Warning: Linear texture filtering not enabled!";
		}

		gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Can not create window: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_WINDOW_OPENGL);
			if (gRenderer == NULL)
			{
				printf("Can not create renderer: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("Can not initialize SDL_image: %s\n", IMG_GetError());
					success = false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

void Game::HandleEvents() {
    bool soundOn=true;
	bool Quit_Menu = false;
	bool Play_Again = false;
	Mix_PlayMusic(gMenuMusic, IS_REPEATITIVE);
	bool collist=true;
	while (!Quit_Menu)
	{
		SDL_Event e_mouse;
		while (SDL_PollEvent(&e_mouse) != 0)
		{
			if (e_mouse.type == SDL_QUIT)
			{
				Quit_Menu = true;
			}

			bool Quit_Game = false;
			HandlePlayButton(&e_mouse, PlayButton, Quit_Menu, Play_Again, gClick);
			HandleInfoButton(&e_mouse, gBackButton,
				InfoButton, BackButton,
				gInstructionTexture, gBackButtonTexture,
				gRenderer, Quit_Game, gClick);
			HandleSoundButton(&e_mouse, SoundButton, gClick,soundOn);
			HandleExitButton(&e_mouse, ExitButton, Quit_Menu, gClick);
		}
		gMenuTexture.Render(0, 0, gRenderer);
		SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
		PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTexture);
		SDL_Rect* currentClip_Sound = &gSoundButton[SoundButton.currentSprite];
		SoundButton.Render(currentClip_Sound, gRenderer, gSoundButtonTexture);
		SDL_Rect* currentClip_Info = &gInfoButton[InfoButton.currentSprite];
		InfoButton.Render(currentClip_Info, gRenderer, gInfoButtonTexture);
		SDL_Rect* currentClip_Exit = &gExitButton[ExitButton.currentSprite];
		ExitButton.Render(currentClip_Exit, gRenderer, gExitButtonTexture);
		SDL_RenderPresent(gRenderer);
	}
    int highscore=0,best=0;
    type=rand()%5;
    int resize=0;
	while (Play_Again)
	{
        if (soundOn) Mix_PlayMusic(gMusic, IS_REPEATITIVE);
		srand(time(NULL));
		SDL_Event e;
		bool Quit = false;
		bool GameState = true;
		while (!Quit)
		{
		    if (Fruit.FruitDistance1<=-100 ) type=(variance1+100)%5;
			if (GameState)
			{
			    p.GetJumpTime();
            SDL_PollEvent(&e);
					if (e.type == SDL_QUIT)
					{
						Quit = true;
						Play_Again = false;
					}



            if (e.type == SDL_KEYDOWN)
                    {
                        if (e.key.keysym.sym == SDLK_SPACE)
                        {
                            if (!p.JumpState())
                            {
                                p.Jump(resize);
                                if (soundOn) Mix_PlayChannel(MIX_CHANNEL,gJump,NOT_REPEATITIVE);
                            }
                            else
                            {
                                p.Gravity(resize);
                            }
                        }
                    }
                    else
                    {
                        p.Gravity(resize);
                    }

                SDL_RWops *file = SDL_RWFromFile("highscore.txt", "r+");
                if (file)
                {
                    SDL_RWread(file, &highscore, sizeof(int), 1);
                    SDL_RWclose(file);
                }
               // Scoring Mechanics
                std::string s;
                s = std::to_string(points);
                score.Text(s,0,0,0,gRenderer);
               if(points > best)
                {
                    best = points;
                }
                if(best > highscore)
                 {
                    SDL_RWops *file = SDL_RWFromFile("highscore.txt", "w+");
                    if (file)
                    {
                        SDL_RWwrite(file, &highscore, sizeof(int), 1);
                        SDL_RWclose(file);
                    }
                 }

                                        // Generation Mechanics
                    std::string s2;
                    s2 = "Death: " + std::to_string(deathcount);
                    death.Text(s2, 255, 255, 255, gRenderer);
                    std::string s5;
                    s5 = "High score: " + std::to_string(best);
                    high.Text(s5, 255, 255, 255, gRenderer);
                    bool flag1 = false, flag2 = false, flag3=false, flag4=false,flag5=false;
                    flag1 = Pipe_Above1.Pipe_Above1Update(variance1, points,frame_Pipe);
                    flag1 = Pipe_Below1.Pipe_Below1Update(variance1,frame_Pipe);
                    flag4 = Fruit.Fruit_Update(variance4,points,frame_Pipe,type);
                    flag5 = Boom.Update_Boom (variance5,frame_Pipe);
                    if (flag1)
                    {
                        srand(SDL_GetTicks());
                        variance1 = rand() % 201 - 100;
                        //last=1;
                    }
                    if (flag4) variance4=variance3;
                    if (flag5) variance5 = rand() % 800;
                    flag2 = Pipe_Above2.Pipe_Above2Update(variance2, points);
                    flag2 = Pipe_Below2.Pipe_Below2Update(variance2);

                    if (flag2)
                    {
                        srand(SDL_GetTicks());
                        variance2 = rand() % 201 - 100;
                        //last=2;
                    }

                    flag3 = Pipe_Above3.Pipe_Above3Update(variance3, points,frame_Pipe);
                    flag3 = Pipe_Below3.Pipe_Below3Update(variance3,frame_Pipe);
                    if (flag3)
                    {
                        srand(SDL_GetTicks());
                        variance3 = rand() % 201 - 100;
                        //last=3;
                    }
                    if (Pipe_Above1.getPipe1X()>=800) last=1;
                    else if (Pipe_Above2.getPipe2X()>=800) last=2;
                    else if (Pipe_Above3.getPipe3X()>=800) last=3;
                    ControlFramePipe(frame_Pipe);
                    ControlFrame(frame_Character);

                    //CollisionDetection();
                    SDL_Rect x=*Boom.getDest();
                    x.w=50;
                    if (CollisionManager::CheckCollision(p.getDest(), Pipe_Above1.getDest()) || CollisionManager::CheckCollision(p.getDest(), Pipe_Below1.getDest()) ||
                    CollisionManager::CheckCollision(p.getDest(), Pipe_Above2.getDest()) || CollisionManager::CheckCollision(p.getDest(), Pipe_Below2.getDest()) ||
                    CollisionManager::CheckCollision(p.getDest(), Pipe_Above3.getDest()) || CollisionManager::CheckCollision(p.getDest(), Pipe_Below3.getDest()) ||
                    (type==3 && CollisionManager::CheckCollision(p.getDest(), Fruit.getDest())) || p.getYpos()>SCREEN_HEIGHT -50 || p.getYpos() < 0 ||
                    CollisionManager::CheckCollision(p.getDest(),&x)  )
                    {
                        if (collist || p.getYpos()>SCREEN_HEIGHT -50 || p.getYpos() < 0 ||
                            CollisionManager::CheckCollision(p.getDest(),&x) )
                      {
                            Die = true;
                            std::string s3,s4;
                            s3 = "Game Over";
                            s4 = "Press any key to start again ! ";
                            if(Die == true)
                            {
                                gameover.Text(s3,255,255,255,gRenderer);
                                press.Text(s4,255,255,255,gRenderer);
                                Mix_PauseMusic(); //Mix_PlayMusic(gMusic,IS_REPEATITIVE);
                                Mix_PlayChannel(MIX_CHANNEL, gLose, NOT_REPEATITIVE);
                                Render();
                                deathcount++;
                                //Reset
                                	points = 0;
                                Die = false;
                                variance1 = rand() % 201 - 100;
                                variance2 = rand() % 201 - 100;
                                variance3 = rand() % 201 - 100;
                                variance5 = rand() % 800;
                                //type=rand()%5;
                                resize=0;
                                collist=true;
                                frame_Type[2]=0;
                                frame_Type[1]=0;
                                frame_Type[0]=0;
                                p.Reset();
                                Pipe_Above1.Reset();
                                Pipe_Below1.Reset();
                                Fruit.Reset();
                                Pipe_Above2.Reset();
                                Pipe_Below2.Reset();
                                Pipe_Above3.Reset();
                                Pipe_Below3.Reset();
                                Fruit.FruitDistance1=Pipe_Above2.getPipe2X()+200;
                                Boom.BoomDistance=900;
                            }
                            //waitUntilKeyPressed
                            SDL_Event event1;
                            while (true) {
                                if ( SDL_WaitEvent(&event1) != 0 && (event1.type == SDL_KEYDOWN || event1.type == SDL_QUIT) )
                                {
                                    if (soundOn) Mix_PlayMusic(gMusic, IS_REPEATITIVE);
                                    break;
                                }
                            SDL_Delay(1000);
                            }

                        }
                        }
                        if(CollisionManager::CheckCollision(p.getDest(),Fruit.getDest())){
                                if (type!=3) Mix_PlayChannel(MIX_CHANNEL,gEat,NOT_REPEATITIVE);

                                if(type==4 )  points+=5;
                                else if(type==2) {
                                    collist=false;
                                    frame_Type[type]=0;
                                }
                                else if(type==1 ) {resize=-30; frame_Type[1]=0;}
                                else if(type==0) {resize=+10; frame_Type[0]=0;}
                                if (last==1) Fruit.FruitDistance1=Pipe_Above1.getPipe1X()+200;
                                    else if(last==2) Fruit.FruitDistance1=Pipe_Above2.getPipe2X()+200;
                                    else if(last ==3 ) Fruit.FruitDistance1=Pipe_Above3.getPipe3X()+200;
                                    else if(last==0) Fruit.FruitDistance1=Pipe_Above3.getPipe3X()+200;
                                    if (Fruit.FruitDistance1<800) Fruit.FruitDistance1+=300;
                                    Render();
                                    type=rand()%5;
                        } else Render();
                        if (!collist) {
                            frame_Type[2]++;
                            timer[2].Text(std::to_string(10-frame_Type[2]/100),255, 234, 0,gRenderer);
                        }
                        if (frame_Type[2]==1000) {
                            collist=true;
                            frame_Type[2]=0;
                        }
                        if (resize==-30) {
                            frame_Type[1]++;
                            timer[1].Text(std::to_string(10-frame_Type[1]/100),165, 42, 42,gRenderer);
                        }
                        if (frame_Type[1]==1000) {frame_Type[1]=0; resize=0;}

                        if (resize==10) {
                            frame_Type[0]++;
                            timer[0].Text(std::to_string(10-frame_Type[0]/100),255, 0, 0,gRenderer);
                        }

                        if (frame_Type[0]==1000) {frame_Type[0]=0; resize=0;}

			}


		}
	}


}
bool Game:: LoadMedia() {
	bool success = true;

	gMusic = Mix_LoadMUS("sound/bkgr_audio.wav");
	if (gMusic == nullptr)
	{
		printf("Failed to load background music%s\n", Mix_GetError());
		success = false;
	}

	gMenuMusic = Mix_LoadMUS("sound/Fluffing-a-Duck.mp3");
	if (gMenuMusic == nullptr)
	{
		printf("Failed to load menu music%s\n", Mix_GetError());
		success = false;
	}
	gClick = Mix_LoadWAV("sound/mouse_click.wav");
	if (gClick == nullptr)
	{
		printf("Failed to load mouse click sound%s\n", Mix_GetError());
		success = false;
	}

	gJump = Mix_LoadWAV("sound/jump_sound.wav");
	if (gJump == nullptr)
	{
		printf("Failed to load jumping sound%s\n", Mix_GetError());
		success = false;
	}
	gEat = Mix_LoadWAV("sound/eat.wav");
	if (gEat==nullptr){
        printf("Failed to load eating sound%s\n", Mix_GetError());
		success = false;
	}

	gLose = Mix_LoadWAV("sound/lose_sound.wav");
	if (gLose == nullptr)
	{
		printf("Failed to load lose sound%s\n", Mix_GetError());
		success = false;
	}

	else
	{
		gFont = TTF_OpenFont("font/PressStart2P.ttf", 15);
		if (gFont == NULL)
		{
			printf("Failed to load font%s\n", Mix_GetError());
			success = false;
		}
		else
		{
			if (!gMenuTexture.LoadFromFile("Img/menu.png", gRenderer))
			{
				std::cout << "Failed to load menu image" << std::endl;
				success = false;
			}

			if (!gInstructionTexture.LoadFromFile("Img/background/info.png", gRenderer))
			{
				std::cout << "Failed to load instruction image" << std::endl;
				success = false;
			}

			if (!gPlayButtonTexture.LoadFromFile("Img/button/play.png", gRenderer))
			{
				std::cout << "Failed to load play_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gPlayButton[i].x = 150 * i;
					gPlayButton[i].y = 0;
					gPlayButton[i].w = 150;
					gPlayButton[i].h = 98;
				}
			}
			if (!gBackButtonTexture.LoadFromFile("Img/button/back_button.png", gRenderer))
			{
				std::cout << "Failed to load back_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gBackButton[i].x = 57 * i;
					gBackButton[i].y = 0;
					gBackButton[i].w = 57;
					gBackButton[i].h = 57;
				}
			}

			if (!gExitButtonTexture.LoadFromFile("Img/button/quit.png", gRenderer))
			{
				std::cout << "Failed to load exit_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gExitButton[i].x = 150 * i;
					gExitButton[i].y = 0;
					gExitButton[i].w = 150;
					gExitButton[i].h = 98;
				}
			}
			gSoundButtonTexture.LoadFromFile("Img/button/audio.png", gRenderer);
			for (int i = 0; i < BUTTON_TOTAL; ++i)
			{
				gSoundButton[i].x = 57 * i;
				gSoundButton[i].y = 0;
				gSoundButton[i].w = 57;
				gSoundButton[i].h = 57;
			}
			gInfoButtonTexture.LoadFromFile("Img/button/help_button.png", gRenderer);
			for (int i = 0; i < BUTTON_TOTAL; ++i)
			{
				gInfoButton[i].x = 150 * i;
				gInfoButton[i].y = 0;
				gInfoButton[i].w = 150;
				gInfoButton[i].h = 98;
			}

			for (int i = 0; i < BACKGROUND_LAYER; ++i)
			{
				if (!g_BackgroundTexture[i].LoadFromFile(SCENCE1[i].c_str(), gRenderer))
				{
					std::cout << "Failed to load background image" << std::endl;
					success = false;
				}
			}
			int j=-1;
            p.CreateTexture("Img/angry bird.png", gRenderer);
            for (int i=0; i<FLYING_FRAMES; i++){
                gCharacterClips[i].x=133*(i%5);
                if (i%5 ==0) j++;
                gCharacterClips[i].y=123*j;
                gCharacterClips[i].w=133;
                gCharacterClips[i].h=123;

            }
			Pipe_Above1.CreateTexture("Img/Pipe_Above.png", gRenderer);
			Pipe_Below1.CreateTexture("Img/Pipe_Below.png", gRenderer);
			Pipe_Above2.CreateTexture("Img/Pipe_Above.png", gRenderer);
			Pipe_Below2.CreateTexture("Img/Pipe_Below.png", gRenderer);
			Pipe_Above3.CreateTexture("Img/Pipe_Above.png", gRenderer);
			Pipe_Below3.CreateTexture("Img/Pipe_Below.png", gRenderer);
			Fruit.CreateTexture("Img/food.png",gRenderer);
            for (int i=0; i<TOTAL_FOOD; i++){
                gFruitClips[i].x=100*i;
                gFruitClips[i].y=0;
                gFruitClips[i].w=100;
                gFruitClips[i].h=100;
            }
			Boom.CreateTexture("Img/boom.png",gRenderer);
            j=-1;
			for (int i=0; i<BOOM_FRAME; i++){
                gBoomClips[i].x=580*(i%2);
                if(i%2==0) j++;
                gBoomClips[i].y=160*j;
                gBoomClips[i].w=580;
                gBoomClips[i].h=160;
			}
			score.CreateFont("font/Number.ttf", 58);
			death.CreateFont("font/calibrib.ttf", 38);
            gameover.CreateFont("font/PressStart2P.ttf",50);
            press.CreateFont("font/PressStart2P.ttf",25);
            high.CreateFont("font/calibrib.ttf", 38);
            timer[2].CreateFont("font/calibrib.ttf",42);
            timer[1].CreateFont("font/calibrib.ttf",42);
            timer[0].CreateFont("font/calibrib.ttf",42);
		}
	}
	return success;
}
void Game::Close() {
	gMenuTexture.Free();
	gInstructionTexture.Free();
	gPlayButtonTexture.Free();
	gInfoButtonTexture.Free();
	gSoundButtonTexture.Free();
	gExitButtonTexture.Free();
	gBackButtonTexture.Free();
	for (int i = 0; i < BACKGROUND_LAYER; ++i)
	{
		g_BackgroundTexture[i].Free();
	}

	Mix_FreeMusic(gMusic);
	Mix_FreeMusic(gMenuMusic);
	Mix_FreeChunk(gClick);
	Mix_FreeChunk(gLose);
	Mix_FreeChunk(gJump);
	gMusic = nullptr;
	gMenuMusic = nullptr;
	gClick = nullptr;
	gLose = nullptr;
	gJump = nullptr;
	gEat=nullptr;

	score.CloseFont();
	death.CloseFont();
	gameover.CloseFont();
    press.CloseFont();
    for (int i=0; i<3; i++)
        timer[i].CloseFont();
	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

                    SDL_Rect de=  {560,90,50,50};
void Game::Render(){
                    SDL_RenderClear(gRenderer);
					RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture, gRenderer);
                    Pipe_Above1.Render(gRenderer);
                    Pipe_Below1.Render(gRenderer);
                    Pipe_Above2.Render(gRenderer);
                    Pipe_Below2.Render(gRenderer);
                    Pipe_Above3.Render(gRenderer);
                    Pipe_Below3.Render(gRenderer);
                    SDL_Rect* currentClip_Fruit = nullptr;
                    currentClip_Fruit = &gFruitClips[type];
                    Fruit.RenderFruit(gRenderer,currentClip_Fruit);
                    score.Render(gRenderer, 375 , 10);
                    death.Render(gRenderer, 10, 10);
                    SDL_Rect* currentClip_Character = nullptr;
                    currentClip_Character = &gCharacterClips[frame_Character%14];
                    if (frame_Type[2]!=0) p.RenderLight(gRenderer,&gCharacterClips[14]);
                    p.Render(gRenderer,currentClip_Character);


                    SDL_RenderCopyEx(gRenderer,Boom.getTexture(),&gBoomClips[frame_Character/4],Boom.getDest(),-45,NULL,SDL_FLIP_NONE);

                    if(Die ==  true )
                    {
                        gameover.Render(gRenderer, 200, 200);
                        press.Render(gRenderer, 50, 300);
                    }
                    if (frame_Type[2]!=0) {
                        timer[2].Render(gRenderer,570,50);
                        de.x=560;
                        SDL_RenderCopy(gRenderer,Fruit.getTexture(),&gFruitClips[2],&de);
                    }
                    if (frame_Type[1]!=0) {
                        timer[1].Render(gRenderer,630,50);
                        de.x=620;
                        SDL_RenderCopy(gRenderer,Fruit.getTexture(),&gFruitClips[1],&de);
                    }
                    if (frame_Type[0]!=0) {
                        timer[0].Render(gRenderer,690,50);
                        de.x=680;
                        SDL_RenderCopy(gRenderer,Fruit.getTexture(),&gFruitClips[0],&de);
                    }
                    high.Render(gRenderer, 550, 10);

                    SDL_RenderPresent(gRenderer);
}
