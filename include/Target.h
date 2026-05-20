#pragma once
#include <SDL2/SDL.h>

class Target
{
public:
    Target(int x,int y,int boyut,int deger,bool durum,SDL_Texture* doku);

    void ciz(SDL_Renderer* renderer , SDL_Rect portalKutusu);
    bool tiklandiMi(int mouseX,int mouseY);

    bool getDurum();
    int getDeger();
    void setDurum(bool yeniDurum);
    void setKonum(int yeniX, int yeniY);
    int getY();

    

private:
int x;
int y;
 int boyut;
 bool durum;
 int deger;
 SDL_Texture* doku;

};

