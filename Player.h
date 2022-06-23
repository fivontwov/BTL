#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

class Player :public Object
{
private:
    double gravity = 0.2;
    int Ypos = 0;
    double accelerator1 = 0;
    double accelerator2 = 0;
    bool inJump = false;
    double jumpHeight = -6;
    double jumpTimer;
    double lastJump = 0;
public:
    void Gravity(int resize);
    void GetJumpTime();
    void Reset();
    int getYpos();
    void Jump(int resize);
    bool JumpState();
    void Render(SDL_Renderer* ren,SDL_Rect*currentClip);
    void RenderLight(SDL_Renderer* ren,SDL_Rect*currentClip);
};
#endif
