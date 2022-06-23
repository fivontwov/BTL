#include"Object.h"

SDL_Texture* Object::getTexture()
{
	return Tex;
}

SDL_Rect* Object::getSrc()
{
	return source;
}

SDL_Rect* Object::getDest()
{
	return destination;
}


void Object::setSrc(int x, int y, int h, int w)
{
	src.x = x;
	src.y = y;
	src.h = h;
	src.w = w;
}

void Object::setDest(int x, int y, int h, int w)
{
	dest.x = x;
	dest.y = y;
	dest.h = h;
	dest.w = w;
}

void Object::CreateTexture(const char* address,SDL_Renderer* ren)
{
	SDL_Surface* surface;
	surface = IMG_Load(address);
	Tex = SDL_CreateTextureFromSurface(ren, surface);
}

