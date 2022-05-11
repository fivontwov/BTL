#ifndef OBJECT_H
#define OBJECT_H
#include"Game_Base.h"


class Object
{
public:
	SDL_Rect src;
	SDL_Rect dest;
	SDL_Rect* source = &src;
	SDL_Rect* destination = &dest;
	SDL_Texture* Tex;


	SDL_Texture* getTexture();
	SDL_Rect* getSrc();
	SDL_Rect* getDest();
	void setSrc(int x, int y, int h, int w);
	void setDest(int x, int y, int h, int w);

	void SetBlendMode(SDL_BlendMode blending);
	void SetAlpha(Uint8 alpha);
	void CreateTexture(const char* address, SDL_Renderer* ren);
};
#endif
