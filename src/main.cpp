#include <SDL2/SDL.h>
#include <iostream>

using namespace std;


int main(int argc, char* argv[]) {
    
    cout << "Karanlik tema refleks oyunu basliyor..." << endl;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Oyun motoru baslatilamadi! Hata: " << SDL_GetError() << std::endl;
        return -1;
    }

    
    SDL_Window* window = SDL_CreateWindow("Reflex Aim Trainer", 
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                          800, 600, SDL_WINDOW_SHOWN);

    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); 
    SDL_RenderClear(renderer); 
    SDL_RenderPresent(renderer); 

    std::cout << "Karanlik tema penceresi acildi! 5 saniye sonra kapanacak..." << std::endl;

   
    SDL_Delay(5000);

    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
