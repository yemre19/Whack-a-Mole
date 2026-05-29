#include "Target.h"

Target::Target(int x,int y,int boyut,int deger,bool durum,SDL_Texture* doku)
{
   this->x=x;
   this->y=y;
   this->boyut=boyut;
   this->deger=deger;
   this->durum=durum;
   this->doku=doku;
}

void Target::ciz(SDL_Renderer* renderer, SDL_Rect portalKutusu)
{
    if (!durum) return;
    
    SDL_Rect makasAlan = portalKutusu;
    
    makasAlan.y = 0;
   makasAlan.h = portalKutusu.y + (portalKutusu.h / 2) + 15;


    SDL_RenderSetClipRect(renderer, &makasAlan);

    SDL_Rect hedefKutusu = {x, y, boyut, boyut};
    SDL_RenderCopy(renderer, doku, nullptr, &hedefKutusu); 

    SDL_RenderSetClipRect(renderer,nullptr);
}

bool Target::tiklandiMi(int mouseX,int mouseY)
{
  int yaricap= boyut/2;
  int merkezX = x + yaricap;
  int merkezY = y + yaricap;

  int gercekHitboxYaricapi = yaricap * 0.75;

  int mesafeX = mouseX - merkezX;
  int mesafeY = mouseY - merkezY;
 
  if ((mesafeX * mesafeX) + (mesafeY * mesafeY) <= (gercekHitboxYaricapi * gercekHitboxYaricapi))
  {
   return true;
  }
  
  return false;
}

int Target::getBoyut() 
{
    return this-> boyut;
}

int Target::getY()
{
   return this-> y;
}

bool Target::getDurum()
{
 return this->durum;
}
int Target::getDeger()
{
return this->deger;

}
void Target::setDurum(bool yeniDurum)
{ 
 this->durum=yeniDurum;
}

void Target::setKonum(int yeniX,int yeniY)
{
   this->x=yeniX;
   this->y=yeniY;
}

int Target::getX()
{
   return this->x;
}

