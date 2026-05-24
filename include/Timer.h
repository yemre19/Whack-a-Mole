#ifndef TIMER_H
#define TIMER_H

#pragma once
#include <SDL2/SDL.h>

class Timer
{
public:
    Timer();
    void baslat();
    void durdur();
    Uint32 gecenSure();
    bool calisiyorMu();
    

private:
   Uint32 baslangicZamani;
   bool calisiyor;

};

#endif