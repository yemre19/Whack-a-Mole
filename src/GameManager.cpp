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


void GameManager::etkinlikleriGozlemle(SDL_Event& etkinlik, bool& oyunCalisiyor, Target& hedef, const vector<SDL_Rect>& portallar)
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
            if (etkinlik.type == SDL_MOUSEBUTTONDOWN && etkinlik.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX = etkinlik.button.x;
                int mouseY = etkinlik.button.y;

                if (hedef.tiklandiMi(mouseX,mouseY))
                {
                   int delikOrtaY = portallar[aktifPortal].y + (portallar[aktifPortal].h / 2);
                   if (mouseY < delikOrtaY)
                   {
                    hedef.setDurum(false);
                    skorYoneticisi.puanEkle(10);
                    cout << "Hedef Vuruldu Skor: " << skorYoneticisi.getSkor() << endl; 
                   }
                   
                }
                
            }
            
        }
        
        else if (mevcutDurum == OyunDurumu::OYUN_SONU)
        {
            if (etkinlik.type == SDL_KEYDOWN && etkinlik.key.keysym.sym==SDLK_r)
            {
            //r ye basinca ana menute donsun
            mevcutDurum = OyunDurumu::ANA_MENU;  
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

    void GameManager::ciz(SDL_Renderer* renderer, SDL_Texture* arkaplan, SDL_Texture* portalResmi, Target& hedef, TTF_Font* font, const vector<SDL_Rect>& portallar) {
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, arkaplan, NULL, NULL);
    SDL_Color yaziRengi = {255, 255, 255, 255};
    if (mevcutDurum == OyunDurumu::ANA_MENU) {
        string menuMetni = "Whack-a-Mole -- BASLAMAK ICIN SPACE'E BASIN";
        SDL_Surface* yuzey = TTF_RenderText_Solid(font, menuMetni.c_str(), yaziRengi);
        SDL_Texture* doku = SDL_CreateTextureFromSurface(renderer, yuzey);
        
        SDL_Rect yaziKonum = { 1280 / 2 - yuzey->w / 2, 720 / 2 - yuzey->h / 2, yuzey->w, yuzey->h };
        SDL_RenderCopy(renderer, doku, NULL, &yaziKonum);
        
        SDL_FreeSurface(yuzey);
        SDL_DestroyTexture(doku);
    }
    else if (mevcutDurum == OyunDurumu::OYUN_ICI) {
        for (const SDL_Rect& portal : portallar)
        {
            SDL_RenderCopy(renderer,portalResmi,nullptr,&portal);
        }
        hedef.ciz(renderer , portallar[aktifPortal]);

        string skorMetni = "Skor: " + to_string(skorYoneticisi.getSkor());
        
        int kalanSaniye = (secilenSure - oyunTimer.gecenSure()) / 1000;
        if (kalanSaniye < 0) kalanSaniye = 0;
        string sureMetni = "Sure: " + to_string(kalanSaniye);

        SDL_Surface* skorYuzey = TTF_RenderText_Solid(font, skorMetni.c_str(), yaziRengi);
        SDL_Texture* skorDoku = SDL_CreateTextureFromSurface(renderer, skorYuzey);
        SDL_Rect skorKonum = {20, 20, skorYuzey->w, skorYuzey->h};
        SDL_RenderCopy(renderer, skorDoku, NULL, &skorKonum);
        SDL_FreeSurface(skorYuzey);
        SDL_DestroyTexture(skorDoku);

        SDL_Surface* sureYuzey = TTF_RenderText_Solid(font, sureMetni.c_str(), yaziRengi);
        SDL_Texture* sureDoku = SDL_CreateTextureFromSurface(renderer, sureYuzey);
        SDL_Rect sureKonum = {20, 60, sureYuzey->w, sureYuzey->h}; 
        SDL_RenderCopy(renderer, sureDoku, NULL, &sureKonum);
        SDL_FreeSurface(sureYuzey);
        SDL_DestroyTexture(sureDoku);
        
    }else if (mevcutDurum == OyunDurumu::OYUN_SONU) {
        string sonMetin = "Sure bitti Skor: " + to_string(skorYoneticisi.getSkor()) + " - Menu icin r ye basin";
        SDL_Surface* yuzey = TTF_RenderText_Solid(font, sonMetin.c_str(), yaziRengi);
        SDL_Texture* doku = SDL_CreateTextureFromSurface(renderer, yuzey);
        
        SDL_Rect yaziKonum = { 1280 / 2 - yuzey->w / 2, 720 / 2 - yuzey->h / 2, yuzey->w, yuzey->h };
        SDL_RenderCopy(renderer, doku, NULL, &yaziKonum);
        
        SDL_FreeSurface(yuzey);
        SDL_DestroyTexture(doku);
    }

    SDL_RenderPresent(renderer);
}