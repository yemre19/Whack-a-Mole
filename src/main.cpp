#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include "Target.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include "ScoreManager.h"
#include <SDL2/SDL_ttf.h>
#include <string>
#include "GameManager.h"


using namespace std;

// Yapay zekadan destek alinarak SDL2 kutuphanesi eklendi.
int main(int argc, char* argv[]) 
{

    srand(time(0));
    
    cout << "Refleks oyunu basliyor..." << endl;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Oyun motoru baslatilamadi! Hata: " << SDL_GetError() << endl;
        return -1;
    }

    if (TTF_Init()== -1)
    {
        cout << "TTF baslatilamadi Hata: " << TTF_GetError() << endl ;
        return -1;
    }

    TTF_Font* oyunFontuBuyuk = TTF_OpenFont("assets/font3.ttf",64 );
    TTF_Font* oyunFontuOrta = TTF_OpenFont("assets/font3.ttf",36 );
    TTF_Font* oyunFontuKucuk = TTF_OpenFont("assets/font3.ttf",24 );
    if (!oyunFontuBuyuk || !oyunFontuOrta || !oyunFontuKucuk)
    {
      cout << "Font yuklenemedi Hata: " << TTF_GetError() << endl ;
    }
    
    

    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("Reflex Aim Trainer",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(renderer, 1280, 720);

    SDL_Texture* arkaplanDokusu = IMG_LoadTexture(renderer, "assets/resm.png");
    //SDL_Texture* girisDokusu = IMG_LoadTexture(renderer, "assets/?.png");

    SDL_Texture* nesneYuvasi = IMG_LoadTexture(renderer, "assets/image.png");
    SDL_Texture* nesne = IMG_LoadTexture(renderer, "assets/1.png");
    vector<SDL_Texture*> patlamaDokulari;
    patlamaDokulari.push_back(IMG_LoadTexture(renderer, "assets/patlama1.png"));
    patlamaDokulari.push_back(IMG_LoadTexture(renderer, "assets/patlama2.png"));
   // patlamaDokulari.push_back(IMG_LoadTexture(renderer, "assets/patlama3.png"));

    Target hedef(0,0,220,10,false,nesne);
    
     
    vector<SDL_Rect> portallar = {
   {210, 120, 220, 100}, {515, 120, 220, 100}, {820, 120, 220, 100},
   {180, 320, 220, 100}, {515, 320, 220, 100}, {850, 320, 220, 100},
   {140, 520, 220, 100}, {515, 520, 220, 100}, {890, 520, 220, 100}
    };

    GameManager oyunYoneticisi;
    bool oyunCalisiyor = true;
    SDL_Event etkinlik;

    while (oyunCalisiyor)
    {
        
        {
            oyunYoneticisi.etkinlikleriGozlemle(etkinlik, oyunCalisiyor, hedef, portallar);
            oyunYoneticisi.guncelle(portallar, hedef);
            oyunYoneticisi.ciz(renderer,arkaplanDokusu,nesneYuvasi,patlamaDokulari,hedef,oyunFontuBuyuk,oyunFontuOrta,oyunFontuKucuk,portallar);
            SDL_Delay(16);
        }
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(nesneYuvasi);
    SDL_DestroyTexture(nesne);
    SDL_DestroyTexture(arkaplanDokusu);
    for (auto doku : patlamaDokulari)
    {
        SDL_DestroyTexture(doku);
    }
    
    TTF_CloseFont(oyunFontuBuyuk);
    TTF_CloseFont(oyunFontuOrta);
    TTF_CloseFont(oyunFontuKucuk);
    IMG_Quit(); 
    SDL_Quit();
    TTF_Quit();
    
    return 0;
}