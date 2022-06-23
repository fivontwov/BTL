#include "Background.h"
#include<cstdlib>


void Background::Render(SDL_Renderer* ren)
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
int boom_Y=-100;
bool Background::Update_Boom (int randX,int frame){
    if (BoomDistance<=-100 || boom_Y>=650){
        BoomDistance=randX;
        boom_Y=-100;
        return true;
    }
    boom_Y++;
	BoomDistance--;
    setSrc(0, 0, 160, 580);
	setDest(BoomDistance,boom_Y, 40, 250);
	return false;
    return true;
}

bool Background::Fruit_Update(int incY,int &points,int frame,int type){
    if (FruitDistance1<=-100){
        FruitDistance1+=900;
        this->incY_F = incY;
        return true;
    }

	FruitDistance1--;
    setSrc(type*100, 0, 100, 100);
	setDest(FruitDistance1,200- incY_F-frame, 50, 50);
	return false;

}

void Background::RenderFruit(SDL_Renderer* ren,SDL_Rect* currentClip){
    SDL_RenderCopy(ren, getTexture(), currentClip, getDest());
}
