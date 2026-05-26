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

    SDL_Texture* arkaplanDokusu = IMG_LoadTexture(renderer, "assets/arkaplan.png");
    SDL_Texture* nesneYuvasi = IMG_LoadTexture(renderer, "assets/nsn.png");
    SDL_Texture* nesne = IMG_LoadTexture(renderer, "assets/nessne.png");

    Target hedef(0,0,150,10,false,nesne);
    
     
    vector<SDL_Rect> portallar = {
        {185, 45, 180, 180}, {550, 45, 180, 180}, {915, 45, 180, 180},
        {185, 270, 180, 180}, {550, 270, 180, 180}, {915, 270, 180, 180},
        {185, 495, 180, 180}, {550, 495, 180, 180}, {915, 495, 180, 180}
    };

    GameManager oyunYoneticisi;
    bool oyunCalisiyor = true;
    SDL_Event etkinlik;

    while (oyunCalisiyor)
    {
        
        {
            oyunYoneticisi.etkinlikleriGozlemle(etkinlik, oyunCalisiyor, hedef, portallar);
            oyunYoneticisi.guncelle(portallar, hedef);
            oyunYoneticisi.ciz(renderer,arkaplanDokusu,nesneYuvasi,hedef,oyunFontu,portallar);
            SDL_Delay(16);
        }
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(nesneYuvasi);
    SDL_DestroyTexture(nesne);
    SDL_DestroyTexture(arkaplanDokusu);
    TTF_CloseFont(oyunFontu);
    IMG_Quit(); 
    SDL_Quit();
    TTF_Quit();
    
    return 0;
}