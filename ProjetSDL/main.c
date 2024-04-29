#include "input.c"
#include "render.c"


const int GAME_SPEED = 150;

int snakeX[25], snakeY[25];

int fruitX, fruitY;
int score;

int gameOver;







void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}



void generateFruit() {
    fruitX = rand() % (WINDOW_WIDTH / GRID_SIZE);
    fruitY = rand() % (WINDOW_HEIGHT / GRID_SIZE);
}


void moveSnake() {
    for (int i = snakeLength; i > 0; --i) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    switch (direction) {
    case 0: 
        snakeY[0] -= 1;
        break;
    case 1: 
        snakeX[0] += 1;
        break;
    case 2: 
        snakeY[0] += 1;
        break;
    case 3: 
        snakeX[0] -= 1;
        break;
    }

    if (snakeX[0] < 0 || snakeX[0] >= WINDOW_WIDTH / GRID_SIZE || snakeY[0] < 0 || snakeY[0] >= WINDOW_HEIGHT / GRID_SIZE) {
        gameOver = true;
    }

    for (int i = 1; i < snakeLength; ++i) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            gameOver = true;
        }
    }

    if (snakeX[0] == fruitX && snakeY[0] == fruitY) {
        score += 1;
        snakeLength++;
        generateFruit();
    }
}



int main(int argc, char* argv[]) {srand(time(NULL));
    if (!init()) {
        return 1;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    generateFruit();

    snakeX[0] = WINDOW_WIDTH / (2 * GRID_SIZE);
    snakeY[0] = WINDOW_HEIGHT / (2 * GRID_SIZE);
    snakeLength = 1;
    direction = -1;
    gameOver = false;
    score = 0;

    Uint32 lastTime = SDL_GetTicks();

    while (!gameOver) {
        Uint32 currentTime = SDL_GetTicks();
        Uint32 deltaTime = currentTime - lastTime;
        if (deltaTime >= GAME_SPEED) {
            handleInput();
            moveSnake();
            render();
            lastTime = currentTime;
        }
    }
    close();
    return 0;
}