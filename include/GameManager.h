#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "Target.h"
#include "ScoreManager.h"
#include "Timer.h"

using namespace std;

enum class OyunDurumu
{
    ANA_MENU,OYUN_ICI,OYUN_SONU
};

class GameManager
{
public:
    GameManager();

    void baslat(int secilenSure, int zorlukSecimi);
    void ciz(SDL_Renderer* renderer, SDL_Texture* arkaplan , SDL_Texture* portalResmi,Target& hedef, TTF_Font* font);
    void etkinlikleriGozlemle(SDL_Event& etkinlik, bool& oyunCalisiyor, Target& hedef, const vector<SDL_Rect>& portallar);
    void guncelle(const vector<SDL_Rect>& portallar, Target& hedef);

    OyunDurumu getDurum();
    void setDurum(OyunDurumu yeniDurum);
    
    

private:
 OyunDurumu mevcutDurum;
 ScoreManager skorYoneticisi;
 Timer oyunTimer;
 Timer spawnTimer;

 int secilenSure;
 int secilenHiz;
 int secilenSpawnSuresi;
 int aktifPortal;

};

#endif