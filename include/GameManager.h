#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "Target.h"
#include "ScoreManager.h"
#include <string>


using namespace std;

enum class OyunDurumu
{
    GIRIS_EKRANI,ANA_MENU,OYUN_ICI,OYUN_SONU
};

class GameManager
{
public:
    GameManager();

    void baslat(int secilenSure, int zorlukSecimi);
    void ciz(SDL_Renderer* renderer, SDL_Texture* arkaplan, SDL_Texture* portalResmi,SDL_Texture* patlamaDokusu, Target& hedef, TTF_Font* font, const vector<SDL_Rect>& portallar);
    void etkinlikleriGozlemle(SDL_Event& etkinlik, bool& oyunCalisiyor, Target& hedef, const vector<SDL_Rect>& portallar);
    void guncelle(const vector<SDL_Rect>& portallar, Target& hedef);

    OyunDurumu getDurum();
    void setDurum(OyunDurumu yeniDurum);
    void yaziCiz(SDL_Renderer* renderer, TTF_Font* font,string metin, int x, int y, SDL_Color renk);
    
    

private:
 OyunDurumu mevcutDurum;
 ScoreManager skorYoneticisi;
 Uint32 oyunBaslangicZamani;
 Uint32 sonSpawnZamani;

 int sureSecimi;
 int zorlukSecimi;

 int secilenSure;
 int secilenHiz;
 int secilenSpawnSuresi;
 int aktifPortal;
 int gecisAnim;

 bool patlama;
 int patlamaX;
 int patlamaY;
 int patlamaBoyut;
 int patlamaSeffaf;

};

#endif