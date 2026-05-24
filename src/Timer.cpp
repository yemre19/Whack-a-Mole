#include "Timer.h"

Timer::Timer()
{
    baslangicZamani = 0;
    calisiyor = false;
}

void Timer::baslat()
{
    calisiyor= true;
    baslangicZamani = SDL_GetTicks();
}

void Timer::durdur()
{
    calisiyor=false;
    baslangicZamani = 0;
}

Uint32 Timer::gecenSure()
{
    if (calisiyor==true)
    {
        return SDL_GetTicks() - baslangicZamani;
    }
    return 0;
    
}

bool Timer::calisiyorMu()
{
    return calisiyor;
}