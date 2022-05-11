#include "Background.h"
#include<cstdlib>

void Background::Render(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, getTexture(), NULL, NULL);
}

void Background::LeaderboardRender(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, getTexture(), getSrc(), getDest());
}

void Background::GroundRender(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, getTexture(), getSrc(), getDest());
}

void Background::PipeRender(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, getTexture(), getSrc(), getDest());
}

bool Background::Pipe_Above1Update(int incY, int &score, int frame)
{
	this->incY1 = incY;
	if (pipeDistance1 <= -100)
	{
		pipeDistance1 += 900;
		return true;
	}
	else
	{
		pipeDistance1-=accelerator;
		if(pipeDistance1 == 150)
        {
            score++;
        }
		setSrc(0, 0, 320, 52);
		setDest(pipeDistance1, -200 + this->incY1+frame, 400, 75);
		return false;
	}
}

bool Background::Pipe_Below1Update(int incY,int frame)
{
	this->incY1 = incY;
	if (pipeDistance1 <= -100)
	{
		pipeDistance1 += 900;
		return true;
	}
	else
	{
		pipeDistance1-=accelerator;
        setSrc(0, 0, 320, 52);
		setDest(pipeDistance1, 375 + this->incY1+frame, 400, 75);
		return false;
	}
}

bool Background::Pipe_Above2Update(int incY, int &score)
{
	this->incY2 = incY;
	if (pipeDistance2 <= -100)
	{
		pipeDistance2 += 900;
        return true;
	}
	else
	{
		pipeDistance2-=accelerator;
		if(pipeDistance2 == 150)
        {
            score++;
        }
		setSrc(0, 0, 320, 52);
		setDest(pipeDistance2, -200 + this->incY2, 400, 75);
		return false;
	}
}

bool Background::Pipe_Below2Update(int incY)
{
	this->incY2 = incY;
	if (pipeDistance2 <= -100)
	{
		pipeDistance2 += 900;
		return true;
	}
	else
	{
		pipeDistance2-=accelerator;
		setSrc(0, 0, 320, 52);
		setDest(pipeDistance2, 375 + this->incY2, 400, 75);
		return false;
	}
}

bool Background::Pipe_Above3Update(int incY, int &score,int frame)
{
	this->incY3 = incY;
	if (pipeDistance3 <= -100)
	{
		pipeDistance3 += 900;
		pipeDistance3-=accelerator;
		return true;
	}
	else
	{
		pipeDistance3-=accelerator;
		if(pipeDistance3 == 150)
        {
            score++;
        }
		setSrc(0, 0, 320, 52);
		setDest(pipeDistance3, -200 + this->incY3-frame, 400, 75);
		return false;
	}
}

bool Background::Pipe_Below3Update(int incY,int frame)
{
	this->incY3 = incY;
	if (pipeDistance3 <= -100)
	{
		pipeDistance3 += 900;
		pipeDistance3-=accelerator;
		return true;
	}
	else
	{
		pipeDistance3-=accelerator;
		setSrc(0, 0, 320, 52);
		setDest(pipeDistance3, 375 + this->incY3-frame, 400, 75);
		return false;
	}
}

int Background::getPipe1Y()
{
	return 300 + this->incY1;
}

int Background::getPipe1X()
{
	return pipeDistance1;
}

int Background::getPipe2Y()
{
	return 300 + this->incY2;
}

int Background::getPipe2X()
{
	return pipeDistance2;
}

int Background::getPipe3Y()
{
	return 300 + this->incY3;
}

int Background::getPipe3X()
{
	return pipeDistance3;
}

void Background::Reset()
{
	pipeDistance1 = 300;
	pipeDistance2 = 600;
	pipeDistance3 = 900;
	incY1 = 0;
	incY2 = 0;
	incY3 = 0;
}

