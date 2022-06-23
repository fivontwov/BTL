#include "Game_Utils.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Object.h"
#include "Game.h"
#include "Background.h"
#include "TextManager.h"

void RenderScrollingBackground(std::vector <double>& offsetSpeed,
	LTexture(&gBackgroundTexture)[BACKGROUND_LAYER],
	SDL_Renderer* gRenderer)
{
	std::vector <double> layer_speed;
	layer_speed.push_back(LAYER_1_SPEED);
	layer_speed.push_back(LAYER_2_SPEED);
	layer_speed.push_back(LAYER_3_SPEED);
	layer_speed.push_back(LAYER_4_SPEED);
	layer_speed.push_back(LAYER_5_SPEED);
	layer_speed.push_back(LAYER_6_SPEED);
	layer_speed.push_back(LAYER_7_SPEED);
	layer_speed.push_back(LAYER_8_SPEED);
	layer_speed.push_back(LAYER_9_SPEED);

	for (int i = 0; i < BACKGROUND_LAYER; ++i)
	{
		offsetSpeed[i] -= layer_speed[i];
		if (offsetSpeed[i] < -gBackgroundTexture[i].GetWidth())
		{
			offsetSpeed[i] = 0;
		}
		gBackgroundTexture[i].Render(offsetSpeed[i], 0, gRenderer);
		gBackgroundTexture[i].Render(offsetSpeed[i] + gBackgroundTexture[i].GetWidth(), 0, gRenderer);
	}
}

void HandlePlayButton(SDL_Event* e,
	Button& PlayButton,
	bool& QuitMenu,
	bool& Play,
	Mix_Chunk* gClick)
{
	if (e->type == SDL_QUIT)
	{
		QuitMenu = true;
	}

	if (PlayButton.IsInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Play = true;
			QuitMenu = true;
			Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		}
	}
	else
	{
		PlayButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}
void HandleSoundButton(SDL_Event* e,
	Button& SoundButton,
	Mix_Chunk* gClick, bool &soundOn) {
	if (SoundButton.IsInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEBUTTONDOWN:
			if (!soundOn) {
				soundOn = true;
				Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
				Mix_ResumeMusic();
				SoundButton.currentSprite = BUTTON_MOUSE_OUT;
				break;
			}
			else if (soundOn){
				soundOn = false;
				Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
				Mix_PauseMusic();
				SoundButton.currentSprite = BUTTON_MOUSE_OVER;
				break;
			}
		}
	}
	if (soundOn)
		SoundButton.currentSprite = BUTTON_MOUSE_OUT;
}

void HandleInfoButton(SDL_Event* e,
	SDL_Rect(&gBackButton)[BUTTON_TOTAL],
	Button& HelpButton,
	Button& BackButton,
	LTexture gInstructionTexture,
	LTexture gBackButtonTexture,
	SDL_Renderer *gRenderer,
	bool &Quit_game,
	Mix_Chunk *gClick)
{
	if (HelpButton.IsInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
			bool ReadDone = false;
			while (!ReadDone)
			{
				do
				{
					if (e->type == SDL_QUIT)
					{
						ReadDone = true;
						Quit_game = true;
						Game::Close();
					}
					else if (BackButton.IsInside(e, SMALL_BUTTON))
					{
						switch (e->type)
						{
						case SDL_MOUSEMOTION:
							BackButton.currentSprite = BUTTON_MOUSE_OVER;
							break;
						case SDL_MOUSEBUTTONDOWN:
							BackButton.currentSprite = BUTTON_MOUSE_OVER;
							Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
							ReadDone = true;
							break;
						}
					}
					else
					{
						BackButton.currentSprite = BUTTON_MOUSE_OUT;
					}
					gInstructionTexture.Render(0, 0, gRenderer);

					SDL_Rect* currentClip_Back = &gBackButton[BackButton.currentSprite];
					BackButton.Render(currentClip_Back, gRenderer, gBackButtonTexture);

					SDL_RenderPresent(gRenderer);
				} while (SDL_PollEvent(e) != 0 && (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION));
			}
			break;
		}
	}
	else
	{
		HelpButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void HandleExitButton(SDL_Event* e,
	Button& ExitButton,
	bool& Quit,
	Mix_Chunk* gClick)
{
	if (ExitButton.IsInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Quit = true;
			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
			break;
		}
	}
	else
	{
		ExitButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void ControlFrame(int &frame)
{
    static int animationTimer=0;
    animationTimer++;
    if (animationTimer % 3==0) {frame ++; animationTimer=0;}
	if (frame >= FLYING_FRAMES)
	{
		frame = 0;
	}
}
bool isRise=true;
void ControlFramePipe(int &frameP){
    static int animationTimerP=0;
    animationTimerP++;
    if (animationTimerP % 3==0) {
        if(frameP<50 && isRise)frameP ++;
        else {
            isRise=false;
            frameP--;
            if (frameP<0) isRise=true;
        }
        animationTimerP=0;
    }
}
