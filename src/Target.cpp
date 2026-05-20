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
    makasAlan.h = portalKutusu.h / 2; 

    SDL_RenderSetClipRect(renderer, &makasAlan);

    SDL_Rect hedefKutusu = {x, y, boyut, boyut};
    SDL_RenderCopy(renderer, doku, nullptr, &hedefKutusu); 

    SDL_RenderSetClipRect(renderer,nullptr);
}

bool Target::tiklandiMi(int mouseX,int mouseY)
{
  if (!durum) return false;
   if (mouseX >= x && mouseX <= (x + boyut) && mouseY >= y && mouseY <= (y + boyut))
   {
    return true;
   }else
   return false;

  
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


