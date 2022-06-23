#include "Player.h"
#include<iostream>

void Player::Render(SDL_Renderer* ren,SDL_Rect* currentClip)
{
	SDL_RenderCopy(ren, getTexture(), currentClip, getDest());
}

void Player:: RenderLight(SDL_Renderer* ren,SDL_Rect*currentClip){
    SDL_RenderCopy(ren, getTexture(), currentClip, getDest());
}
int Player::getYpos()
{
	return Ypos;
}

void Player::Gravity(int resize)
{
	if (JumpState())
	{
		accelerator1 = accelerator1 + 0.035;
		accelerator2 = accelerator2 + 0.035;
		jumpHeight = jumpHeight + gravity;
		Ypos = Ypos + gravity + accelerator1 + accelerator2 + jumpHeight;
		setDest(150, Ypos, CHARACTER_HEIGHT+resize, CHARACTER_WIDTH+resize);
		if (jumpHeight > 0)
		{
			inJump = false;
			jumpHeight = -6;
		}
	}
	else
	{

		accelerator1 = accelerator1 + 0.035;
		accelerator2 = accelerator2 + 0.035;
		Ypos = Ypos + gravity + accelerator1 + accelerator2;
		setDest(150, Ypos, CHARACTER_HEIGHT+resize, CHARACTER_WIDTH+resize);
	}

}

void Player::Jump(int resize)
{
	if (jumpTimer - lastJump > 50)
	{
		accelerator1 = 0;
		accelerator2 = 0;
		inJump = true;
		lastJump = jumpTimer;
	}
	else
	{
		Gravity(resize);
	}
}

void Player::GetJumpTime()
{
	jumpTimer = SDL_GetTicks();
}

bool Player::JumpState()
{
	return inJump;
}

void Player::Reset()
{
	accelerator1 = 0;
	accelerator2 = 0;
	Ypos = 256;
	lastJump = 0;
}


