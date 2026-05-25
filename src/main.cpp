#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include "Target.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Timer.h"
#include "ScoreManager.h"
#include <SDL2/SDL_ttf.h>
#include <string>
#include "GameManager.h"


using namespace std;

// Yapay zekadan destek alinarak SDL2 kutuphanesi eklendi.
int main(int argc, char* argv[]) {

    srand(time(0));
    
    cout << "Karanlik tema refleks oyunu basliyor..." << endl;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Oyun motoru baslatilamadi! Hata: " << SDL_GetError() << endl;
        return -1;
    }

    if (TTF_Init()== -1)
    {
        cout << "TTF baslatilamadi Hata: " << TTF_GetError() << endl ;
        return -1;
    }

    TTF_Font* oyunFontu = TTF_OpenFont("assets/font.otf",28 );
    if (oyunFontu == nullptr)
    {
      cout << "Font yuklenemedi Hata: " << TTF_GetError() << endl ;
    }
    
    

    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("Reflex Aim Trainer",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(renderer, 1280, 720);

    bool oyunCalisiyor = true;
    SDL_Event etkinlik;

    SDL_Texture* arkaplanDokusu = IMG_LoadTexture(renderer, "assets/arkaplan.png");
    if (arkaplanDokusu == nullptr) {
        cout << "Arka plan yuklenemedi Hata: " << IMG_GetError() << endl;
    }

    SDL_Texture* nesneYuvasi = IMG_LoadTexture(renderer, "assets/nesneyuvasi.png");
    if (nesneYuvasi== nullptr)
    {
        cout << "Portal resmi yuklenmedi Hata: " << IMG_GetError() << endl;
    }

    SDL_Texture* nesne = IMG_LoadTexture(renderer, "assets/nesne-Photoroom.png");
    if (nesne == nullptr)
    {
        cout << "Nesne resmi yuklenmedi Hata: " << IMG_GetError() << endl;
    }

    Target hedef(0,0,150,10,false,nesne);
    
     
    vector<SDL_Rect> portallar = {
        {320, 85, 150, 150}, {565, 85, 150, 150}, {810, 85, 150, 150},
        {320, 285, 150, 150}, {565, 285, 150, 150}, {810, 285, 150, 150},
        {320, 485, 150, 150}, {565, 485, 150, 150}, {810, 485, 150, 150}
    };


    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); 
    SDL_RenderClear(renderer); 

    
    SDL_RenderCopy(renderer, arkaplanDokusu, NULL, NULL);




    int rastgele = rand() % 9;

    int baslangicY= portallar[rastgele].y + portallar[rastgele].h;
    hedef.setKonum(portallar[rastgele].x, baslangicY);
    hedef.setDurum(true);

    Timer spawnTimer;
    spawnTimer.baslat();

    ScoreManager skorYoneticisi;

    while (oyunCalisiyor)
    {
        while (SDL_PollEvent(&etkinlik))
        {
            if (etkinlik.type==SDL_QUIT)
            {
                oyunCalisiyor=false;
            }
            
            if (etkinlik.type == SDL_MOUSEBUTTONDOWN)
            {
                if (etkinlik.button.button == SDL_BUTTON_LEFT)
                {
                    int mouseX = etkinlik.button.x;
                    int mouseY = etkinlik.button.y;

                    if (hedef.tiklandiMi(mouseX,mouseY))
                    {
                        int delikOrtaY = portallar[rastgele ].y + (portallar[rastgele].h/2);

                        if (mouseY < delikOrtaY)  
                        {
                            hedef.setDurum(false);
                            skorYoneticisi.puanEkle(10);
                            cout << "Hedef Vuruldu" << "Mevcut Skor: " << skorYoneticisi.getSkor() << endl ;
                        }
                        

                    }
                    
                }
                
            }
            
        }

        if (hedef.getDurum() == false || spawnTimer.gecenSure() > 500)
        {
            rastgele = rand() % 9;
            baslangicY = portallar[rastgele].y + (portallar[rastgele].h/2);
            hedef.setKonum(portallar[rastgele].x, baslangicY);
            hedef.setDurum(true);
            spawnTimer.baslat();
        }
        

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); 
    SDL_RenderClear(renderer); 
    SDL_RenderCopy(renderer, arkaplanDokusu, NULL, NULL);

    string skorMetni= "Skor: " + to_string(skorYoneticisi.getSkor());
    SDL_Color yaziRengi= {255,255,255,255};
    SDL_Surface* yaziYuzeyi = TTF_RenderText_Solid(oyunFontu, skorMetni.c_str(), yaziRengi);
    SDL_Texture* yaziDokusu = SDL_CreateTextureFromSurface(renderer, yaziYuzeyi);
    SDL_Rect yaziTablosu;
    yaziTablosu.x=20;
    yaziTablosu.y=20;
    yaziTablosu.w= yaziYuzeyi->w;
    yaziTablosu.h = yaziYuzeyi->h;

    SDL_RenderCopy(renderer, yaziDokusu, NULL , &yaziTablosu);
    SDL_FreeSurface(yaziYuzeyi);
    SDL_DestroyTexture(yaziDokusu);

    for (const SDL_Rect& portal : portallar)
    {
        SDL_RenderCopy(renderer, nesneYuvasi ,nullptr, &portal);
    }
    hedef.ciz(renderer, portallar[rastgele]);

    
    if (hedef.getDurum() == true && hedef.getY() > portallar[rastgele].y)
    {
        hedef.setKonum(portallar[rastgele].x,hedef.getY() -5 );
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(16);
    }
    
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(nesneYuvasi);
    SDL_DestroyTexture(nesne);
    IMG_Quit(); 
    SDL_Quit();
    TTF_CloseFont(oyunFontu);
    TTF_Quit();
    
    return 0;
}