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

void Target::ciz(SDL_Renderer* renderer)
{
    if (!durum) return;

    SDL_Rect hedefKutusu = {x, y, boyut, boyut};
    SDL_RenderCopy(renderer, doku, nullptr, &hedefKutusu);
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


