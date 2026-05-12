#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include "Target.h"

using namespace std;


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

    SDL_Texture* arkaplanDokusu = IMG_LoadTexture(renderer, "assets/arkaplan.png");
    if (arkaplanDokusu == nullptr) {
        cout << "Arka plan yuklenemedi! Hata: " << IMG_GetError() << endl;
    }

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); 
    SDL_RenderClear(renderer); 

    
    SDL_RenderCopy(renderer, arkaplanDokusu, NULL, NULL);
    SDL_RenderPresent(renderer);
    
   

    cout << "Hedef ekranda! 5 saniye sonra kapanacak..." << endl;
    SDL_Delay(5000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit(); 
    SDL_Quit();

    return 0;
}