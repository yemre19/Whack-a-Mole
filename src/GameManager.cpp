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
    sureSecimi=30;
    zorlukSecimi=2;
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
 secilenSure = sureSecimiSaniye * 1000;

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
 oyunBaslangicZamani = SDL_GetTicks();
 sonSpawnZamani = SDL_GetTicks();
 skorYoneticisi.sifirla();

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
           if (etkinlik.type == SDL_MOUSEBUTTONDOWN && etkinlik.button.button == SDL_BUTTON_LEFT)
            {
                int fareX = etkinlik.button.x;
                int fareY = etkinlik.button.y;

                if (fareY >= 300 && fareY <= 350) {
                    if (fareX >= 450 && fareX <= 600) sureSecimi = 30;
                    else if (fareX >= 680 && fareX <= 830) sureSecimi = 60;
                }
                if (fareY >= 400 && fareY <= 450) {
                    if (fareX >= 350 && fareX <= 500) zorlukSecimi = 1;
                    else if (fareX >= 550 && fareX <= 700) zorlukSecimi = 2;
                    else if (fareX >= 750 && fareX <= 900) zorlukSecimi = 3;
                }if (fareX >= 500 && fareX <= 780 && fareY >= 550 && fareY <= 600) {
                    baslat(sureSecimi, zorlukSecimi);
                    hedef.setDurum(false);
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

         Uint32 suankiZaman = SDL_GetTicks();

         if (suankiZaman - oyunBaslangicZamani >= secilenSure)
         {
            mevcutDurum=OyunDurumu::OYUN_SONU;
            return;
         }
         
         if (!hedef.getDurum() || (suankiZaman - sonSpawnZamani > secilenSpawnSuresi))
         {
            aktifPortal = rand() %  portallar.size();
            int baslangicY = portallar[aktifPortal].y + (portallar[aktifPortal].h- hedef.getBoyut()/2);
            hedef.setKonum(portallar[aktifPortal].x + (portallar[aktifPortal].w / 2) - (hedef.getBoyut() / 2),baslangicY);
            hedef.setDurum(true);
            sonSpawnZamani= suankiZaman;
         }
         
         if (hedef.getDurum() && hedef.getY() > portallar[aktifPortal].y - 100)
         {
            hedef.setKonum(portallar[aktifPortal].x, hedef.getY() - secilenHiz);
         }
         
    }

    void GameManager::yaziCiz(SDL_Renderer* renderer, TTF_Font* font, string metin, int x, int y, SDL_Color renk)
    {
        SDL_Surface* yuzey = TTF_RenderText_Solid(font, metin.c_str(), renk);
        SDL_Texture* doku = SDL_CreateTextureFromSurface(renderer, yuzey);
        SDL_Rect konum = { x, y, yuzey->w, yuzey->h };
        SDL_RenderCopy(renderer, doku, NULL, &konum);
        SDL_FreeSurface(yuzey);
        SDL_DestroyTexture(doku);

    }

    void GameManager::ciz(SDL_Renderer* renderer, SDL_Texture* arkaplan, SDL_Texture* portalResmi, Target& hedef, TTF_Font* font, const vector<SDL_Rect>& portallar) {
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, arkaplan, NULL, NULL);
    SDL_Color yaziRengi = {255, 255, 255, 255};
    if (mevcutDurum == OyunDurumu::ANA_MENU) {
        SDL_Color beyaz = {200, 200, 200, 255};
        SDL_Color neonMavi = {0, 255, 255, 255};
        SDL_Color baslaRenk = {255, 50, 150, 255};
        yaziCiz(renderer, font, "WHACK-A-MOLE", 400, 150, beyaz);
        yaziCiz(renderer, font, "[ 30 SANIYE ]", 450, 300, (sureSecimi == 30) ? neonMavi : beyaz);
        yaziCiz(renderer, font, "[ 60 SANIYE ]", 680, 300, (sureSecimi == 60) ? neonMavi : beyaz);
        yaziCiz(renderer, font, "[ KOLAY ]", 350, 400, (zorlukSecimi == 1) ? neonMavi : beyaz);
        yaziCiz(renderer, font, "[ ORTA ]",  550, 400, (zorlukSecimi == 2) ? neonMavi : beyaz);
        yaziCiz(renderer, font, "[ ZOR ]",   750, 400, (zorlukSecimi == 3) ? neonMavi : beyaz);
        yaziCiz(renderer, font, " OYUNA BASLA ", 520, 550, baslaRenk);
    }
    else if (mevcutDurum == OyunDurumu::OYUN_ICI) {
        for (const SDL_Rect& portal : portallar)
        {
            SDL_RenderCopy(renderer,portalResmi,nullptr,&portal);
        }
        hedef.ciz(renderer , portallar[aktifPortal]);

        string skorMetni = "Skor: " + to_string(skorYoneticisi.getSkor());
        
        int kalanSaniye = (secilenSure - (SDL_GetTicks() - oyunBaslangicZamani)) / 1000;
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