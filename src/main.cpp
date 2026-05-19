#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include "Target.h"
#include <vector>

using namespace std;

// Yapay zekadan destek alinarak SDL2 kutuphanesi eklendi.
int main(int argc, char* argv[]) {
    
    cout << "Karanlik tema refleks oyunu basliyor..." << endl;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Oyun motoru baslatilamadi! Hata: " << SDL_GetError() << endl;
        return -1;
    }

    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("Reflex Aim Trainer", 
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                          800, 600, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

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
     
    vector<SDL_Rect> portallar = {
        {150, 150, 200, 200},
        {350, 150, 200, 200},
        {550, 150, 200, 200},
        {150, 350, 200, 200},
        {350, 350, 200, 200},
        {550, 350, 200, 200}
    };


    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); 
    SDL_RenderClear(renderer); 

    
    SDL_RenderCopy(renderer, arkaplanDokusu, NULL, NULL);


    while (oyunCalisiyor)
    {
        while (SDL_PollEvent(&etkinlik))
        {
            if (etkinlik.type==SDL_QUIT)
            {
                oyunCalisiyor=false;
            }
            
        }
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); 
    SDL_RenderClear(renderer); 
    SDL_RenderCopy(renderer, arkaplanDokusu, NULL, NULL);

    for (const SDL_Rect& portal : portallar)
    {
        SDL_RenderCopy(renderer, nesneYuvasi ,nullptr, &portal);
    }
    

    SDL_RenderPresent(renderer);
    }
    
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(nesneYuvasi);
    IMG_Quit(); 
    SDL_Quit();

    return 0;
}