#include "init.c"
int snakeLength;
const int GRID_SIZE = 20;


void render() {
    SDL_SetRenderDrawColor(renderer, 122, 122, 122, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < snakeLength; ++i) {
        SDL_Rect rect = { snakeX[i] * GRID_SIZE, snakeY[i] * GRID_SIZE,
            GRID_SIZE, GRID_SIZE };
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect fruitRect = { fruitX * GRID_SIZE, fruitY * GRID_SIZE,
        GRID_SIZE, GRID_SIZE };
    SDL_RenderFillRect(renderer, &fruitRect);

    SDL_RenderPresent(renderer);
}
