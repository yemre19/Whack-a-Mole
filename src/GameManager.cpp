#include "GameManager.h"
#include <iostream>
#include <string>

GameManager::GameManager()
{
    mevcutDurum = OyunDurumu::ANA_MENU;
    secilenSure=30;
    secilenHiz=5;
    secilenSpawnSuresi=2000;
    aktifPortal=0;
}

void GameManager::setDurum(OyunDurumu yeniDurum)
{
    mevcutDurum=yeniDurum;
}

OyunDurumu GameManager::getDurum()
{
    return this->mevcutDurum;
}

void GameManager::baslat(int sureSecimiSaniye,int zorlukSecimi)
{
 secilenSure = sureSecimiSaniye * 100;

 if (zorlukSecimi == 1)
 {
    secilenHiz = 4;
    secilenSpawnSuresi=2000;
 }

  if (zorlukSecimi == 2)
 {
    secilenHiz = 7;
    secilenSpawnSuresi=1000;
 }

  if (zorlukSecimi == 3)
 {
    secilenHiz = 11;
    secilenSpawnSuresi=500;
 }
 

 mevcutDurum = OyunDurumu::OYUN_ICI;
 oyunTimer.baslat();
 spawnTimer.baslat();
}


void GameManager::etkinlikleriGozlemle(SDL_Event& etkinlik, bool& oyunCalisiyor)
    {
      while (SDL_PollEvent(&etkinlik))
      {
        if (etkinlik.type ==SDL_QUIT)
        {
            oyunCalisiyor=false;
        }
        if (mevcutDurum== OyunDurumu::ANA_MENU)
        {
            if (etkinlik.type=SDL_KEYDOWN)
            {
                //test amacli space tusuna basinca 30 saniyelik 2.zorlukta oyunu baslatsin
                if (etkinlik.key.keysym.sym == SDLK_SPACE)
                {
                    baslat(30,2);
                }
                
            }

            
        }else if (mevcutDurum==OyunDurumu::OYUN_ICI)
        {
            if (etkinlik.type == SDL_MOUSEBUTTONDOWN)
            {
                if (etkinlik.button.button=SDL_BUTTON_LEFT)
                {
                   
                }
                
            }
            
        }
        
        else if (mevcutDurum == OyunDurumu::OYUN_SONU)
        {
            if (etkinlik.type == SDL_KEYDOWN)
            {
                if (etkinlik.key.keysym.sym=SDLK_r)
                {
                    //r ye basinca ana menute donsun
                    mevcutDurum = OyunDurumu::ANA_MENU;
                }
                
            }
            
        }
        
        
      }
      
    }

    void GameManager::guncelle(const vector<SDL_Rect>& portallar, Target& hedef)
    {
         if (mevcutDurum != OyunDurumu::OYUN_ICI)
         {
            return;
         }
         if (oyunTimer.gecenSure() >= secilenSure)
         {
            mevcutDurum = OyunDurumu::OYUN_SONU;
            return;
         }

         if (!hedef.getDurum() || spawnTimer.gecenSure() > secilenSpawnSuresi)
         {
            aktifPortal = rand() % portallar.size();
            int baslangicY = portallar[aktifPortal].y + (portallar[aktifPortal].h/2);
            hedef.setKonum(portallar[aktifPortal].x,baslangicY);
            hedef.setDurum(true);
            spawnTimer.baslat();
         }
         
         if (hedef.getDurum() && hedef.getY() > portallar[aktifPortal].y)
         {
            hedef.setKonum(portallar[aktifPortal].x, hedef.getY() - secilenHiz);
         }
         
         
    }