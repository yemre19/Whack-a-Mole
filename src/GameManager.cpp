#include "GameManager.h"
#include <iostream>
#include <string>
#include "Target.h"


GameManager::GameManager()
{
    mevcutDurum = OyunDurumu::GIRIS_EKRANI;
    gecisAnim=255;
    secilenSure=30;
    secilenHiz=5;
    secilenSpawnSuresi=2000;
    aktifPortal=0;
    sureSecimi=30;
    zorlukSecimi=2;
    patlama = false;
    patlamaX = 0;
    patlamaY = 0;
    patlamaBoyut = 0;
    //patlamaSeffaf = 0;
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
    secilenSpawnSuresi=750;
 }

  if (zorlukSecimi == 2)
 {
    secilenHiz = 7;
    secilenSpawnSuresi=600;
 }

  if (zorlukSecimi == 3)
 {
    secilenHiz = 11;
    secilenSpawnSuresi=500;
 }
 if (zorlukSecimi == 4)
 {
    secilenHiz = 12;
    secilenSpawnSuresi=300;
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
        }if (mevcutDurum==OyunDurumu::GIRIS_EKRANI)
        {
            if (etkinlik.type == SDL_MOUSEBUTTONDOWN && etkinlik.button.button == SDL_BUTTON_LEFT)
            {
                int fareX = etkinlik.button.x;
                int fareY = etkinlik.button.y;

                if (fareX >= 500 && fareX <=700 && fareY >= 500 && fareY <= 550)
                {
                    mevcutDurum=OyunDurumu::ANA_MENU;
                    gecisAnim=250;
                    
                }
                
            }
            
        }
        
         else if (mevcutDurum== OyunDurumu::ANA_MENU)
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
                    if (fareX >= 250 && fareX <= 400) zorlukSecimi = 1;
                    else if (fareX >= 450 && fareX <= 600) zorlukSecimi = 2;
                    else if (fareX >= 650 && fareX <= 800) zorlukSecimi = 3;
                    else if (fareX >= 850 && fareX <= 1000) zorlukSecimi = 4;
                }if (fareX >= 500 && fareX <= 780 && fareY >= 550 && fareY <= 600) {
                    baslat(sureSecimi, zorlukSecimi);
                    hedef.setDurum(false);
                    gecisAnim=250;
                    
                }
            }
            
            
            
        }else if (mevcutDurum==OyunDurumu::OYUN_ICI)
        {
            if (etkinlik.type == SDL_MOUSEBUTTONDOWN && etkinlik.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX = etkinlik.button.x;
                int mouseY = etkinlik.button.y;
                int delikOrtaY = portallar[aktifPortal].y + (portallar[aktifPortal].h / 2);

                if (hedef.getDurum() == true && hedef.tiklandiMi(mouseX,mouseY) && mouseY < delikOrtaY)
                {
                   static Uint32 sonVurusZamani = 0;
                   Uint32 suankiZaman = SDL_GetTicks();



                   if (suankiZaman - sonVurusZamani > 150)
                   {

                    sonVurusZamani = suankiZaman;

                    hedef.setDurum(false);
                    skorYoneticisi.puanEkle(10);
                    vurulanHedef++;
                    cout << "Hedef Vuruldu Skor: " << skorYoneticisi.getSkor() << endl; 
                    patlama = true;
                    patlamaX = hedef.getX();
                    patlamaY = hedef.getY();
                    patlamaBoyut = hedef.getBoyut();
                    patlamaFrame = 0;
                    sonFrameZamani = SDL_GetTicks();
                    //patlamaSeffaf =255;
                
                   }
                   


                   
                   
                }
                
            }
        
            
        }
        
        else if (mevcutDurum == OyunDurumu::OYUN_SONU)
        {
            if (etkinlik.type == SDL_KEYDOWN && etkinlik.key.keysym.sym==SDLK_r)
            {

                toplamHedef = 0;
                vurulanHedef = 0;
                skorYoneticisi.sifirla();
                oyunBaslangicZamani = SDL_GetTicks();
                mevcutDurum = OyunDurumu::GIRIS_EKRANI;  
                gecisAnim=250;
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
            toplamHedef++;
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

    void GameManager::ciz(SDL_Renderer* renderer, SDL_Texture* arkaplan, SDL_Texture* portalResmi,const vector<SDL_Texture*>& patlamaDokulari, Target& hedef, TTF_Font* font, const vector<SDL_Rect>& portallar) {
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, arkaplan, NULL, NULL);
    SDL_Color yaziRengi = {255, 255, 255, 255};
    if (mevcutDurum == OyunDurumu::GIRIS_EKRANI)
    {
        SDL_SetRenderDrawColor(renderer,15, 15, 20,255);
        SDL_RenderClear(renderer);
        SDL_Color beyaz = {200, 200, 200, 255};
        SDL_Color neonPembe = {255, 50, 150, 255};

        yaziCiz(renderer, font , "WHACK-A-MOLE" , 400,250,beyaz);
        yaziCiz(renderer, font , "OYUNA BASLA" , 520,500,neonPembe);
    }
    
    else if (mevcutDurum == OyunDurumu::ANA_MENU) {
        SDL_Color beyaz = {200, 200, 200, 255};
        SDL_Color neonMavi = {0, 255, 255, 255};
        SDL_Color baslaRenk = {255, 50, 150, 255};
        yaziCiz(renderer, font, "WHACK-A-MOLE", 400, 150, beyaz);
        yaziCiz(renderer, font, "[ 30 SANIYE ]", 450, 300, (sureSecimi == 30) ? neonMavi : beyaz);
        yaziCiz(renderer, font, "[ 60 SANIYE ]", 680, 300, (sureSecimi == 60) ? neonMavi : beyaz);
        yaziCiz(renderer, font, "[ KOLAY ]", 250, 400, (zorlukSecimi == 1) ? neonMavi : beyaz);
        yaziCiz(renderer, font, "[ ORTA ]",  450, 400, (zorlukSecimi == 2) ? neonMavi : beyaz);
        yaziCiz(renderer, font, "[ ZOR ]",   650, 400, (zorlukSecimi == 3) ? neonMavi : beyaz);
        yaziCiz(renderer, font, "[ COK ZOR ]",850, 400, (zorlukSecimi == 4) ? neonMavi : beyaz);
        yaziCiz(renderer, font, " ONAYLA VE BASLA ", 520, 550, baslaRenk);
    }
    else if (mevcutDurum == OyunDurumu::OYUN_ICI) {
        for (const SDL_Rect& portal : portallar)
        {
            SDL_RenderCopy(renderer,portalResmi,nullptr,&portal);
        }
        hedef.ciz(renderer , portallar[aktifPortal]);
        

        if (patlama)
        {
            SDL_Rect patlamaKutusu={patlamaX,patlamaY,patlamaBoyut,patlamaBoyut};
            SDL_RenderCopy(renderer,patlamaDokulari[patlamaFrame],NULL,&patlamaKutusu);
            Uint32 suankiZaman = SDL_GetTicks();

            if (suankiZaman - sonFrameZamani > 60) {
            sonFrameZamani = suankiZaman;
            patlamaFrame++;

            if (patlamaFrame >= patlamaDokulari.size()) {
                patlama = false;
            }
            
        }
    }

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
        SDL_Color beyaz = {200, 200, 200, 255};
        SDL_Color neonMavi = {0, 255, 255, 255};

        int basariYuzde = 0;
        if (toplamHedef > 0)
        {
           basariYuzde = (vurulanHedef * 100) / toplamHedef;
        }
        
        string skorMetni = "TOPLAM SKOR: " + to_string(skorYoneticisi.getSkor());
        string isabetOrani = "ISABET ORANI: " + to_string(vurulanHedef) + " / " + to_string(toplamHedef);
        string  yuzde = "BASARI YUZDESI: %" + to_string(basariYuzde);

        yaziCiz(renderer,font , "SURE BITTI",400,400,beyaz);
        yaziCiz(renderer, font, skorMetni, 450, 300, neonMavi);
        yaziCiz(renderer, font, isabetOrani, 450, 350, neonMavi);
        yaziCiz(renderer,font, yuzde , 450,400,neonMavi);
        yaziCiz(renderer, font, "Ana menu icin 'R' tusuna basin", 420, 550, beyaz);

 }
    if (gecisAnim > 0)
    {
        SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer,0,0,0,gecisAnim);

        SDL_Rect tamEkran = {0,0,1280,720};
        SDL_RenderFillRect(renderer, &tamEkran);

        gecisAnim -=8;
        if (gecisAnim < 0) gecisAnim = 0;
    }
    

 
    SDL_RenderPresent(renderer);
}

