#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Object.h"

class Background :public Object
{
private:
	int distance1 = 0;
	int distance2 = 0;
	int pipeDistance1 = 400;
	int pipeDistance2 = 700;
	int pipeDistance3 = 1000;
	int incY1 = 0;
	int incY2 = 0;
	int incY3 = 0;
	int accelerator=1;

public:
	bool Pipe_Above1Update(int incY, int &score,int frame);
	bool Pipe_Below1Update(int incY,int frame);
	bool Pipe_Above2Update(int incY, int& score);
	bool Pipe_Below2Update(int incY);
	bool Pipe_Above3Update(int incY, int& score,int frame);
	bool Pipe_Below3Update(int incY,int frame);
	void Reset();
	int getPipe1X();
	int getPipe1Y();
	int getPipe2X();
	int getPipe2Y();
	int getPipe3X();
	int getPipe3Y();
	void Render(SDL_Renderer* ren);
	void GroundRender(SDL_Renderer* ren);
	void LeaderboardRender(SDL_Renderer* ren);
	void PipeRender(SDL_Renderer* ren);
};

#endif
