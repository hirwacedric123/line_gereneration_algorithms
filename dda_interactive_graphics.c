#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// DDA Line Drawing Algorithm
void drawLineDDA(SDL_Renderer* renderer, int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    
    float xIncrement = (float)dx / (float)steps;
    float yIncrement = (float)dy / (float)steps;
    
    float x = x1;
    float y = y1;
    
    printf("Drawing line: (%d,%d) -> (%d,%d) | dx=%d dy=%d steps=%d\n", 
           x1, y1, x2, y2, dx, dy, steps);
    
    for (int i = 0; i <= steps; i++) {
        SDL_RenderDrawPoint(renderer, (int)round(x), (int)round(y));
        x += xIncrement;
        y += yIncrement;
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed! %s\n", SDL_GetError());
        return 1;
    }
    
    SDL_Window* window = SDL_CreateWindow(
        "DDA Line Drawing - Interactive (Click to draw!)",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    
    if (!window) {
        printf("Window creation failed! %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed! %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    printf("\n╔═══════════════════════════════════════════════════════╗\n");
    printf("║  DDA Interactive Line Drawing                         ║\n");
    printf("╚═══════════════════════════════════════════════════════╝\n\n");
    printf("Instructions:\n");
    printf("  1. Click to set the starting point (you'll see a small circle)\n");
    printf("  2. Click again to set the ending point and draw the line\n");
    printf("  3. Press 'C' to clear the screen\n");
    printf("  4. Press 'ESC' or close window to exit\n\n");
    
    // Clear with white background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    
    int quit = 0;
    SDL_Event e;
    int clickCount = 0;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = 1;
                }
                else if (e.key.keysym.sym == SDLK_c) {
                    // Clear screen
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer);
                    clickCount = 0;
                    printf("\nScreen cleared!\n");
                }
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = e.button.x;
                    int mouseY = e.button.y;
                    
                    if (clickCount == 0) {
                        // First click - starting point
                        x1 = mouseX;
                        y1 = mouseY;
                        clickCount = 1;
                        
                        // Draw a small circle to show starting point
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                        for (int dx = -3; dx <= 3; dx++) {
                            for (int dy = -3; dy <= 3; dy++) {
                                if (dx*dx + dy*dy <= 9) {
                                    SDL_RenderDrawPoint(renderer, x1 + dx, y1 + dy);
                                }
                            }
                        }
                        SDL_RenderPresent(renderer);
                        
                        printf("\nStart point: (%d, %d) - Click again for end point\n", x1, y1);
                    }
                    else {
                        // Second click - ending point, draw line
                        x2 = mouseX;
                        y2 = mouseY;
                        
                        printf("End point: (%d, %d)\n", x2, y2);
                        
                        // Draw the line using DDA
                        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                        drawLineDDA(renderer, x1, y1, x2, y2);
                        
                        // Draw end point marker
                        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                        for (int dx = -3; dx <= 3; dx++) {
                            for (int dy = -3; dy <= 3; dy++) {
                                if (dx*dx + dy*dy <= 9) {
                                    SDL_RenderDrawPoint(renderer, x2 + dx, y2 + dy);
                                }
                            }
                        }
                        
                        SDL_RenderPresent(renderer);
                        clickCount = 0;
                        
                        printf("✓ Line drawn! Click again to draw another line.\n");
                    }
                }
            }
        }
        
        SDL_Delay(10);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    printf("\nProgram closed.\n");
    return 0;
}

