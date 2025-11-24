#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// DDA Line Drawing Algorithm
void drawLineDDA(SDL_Renderer* renderer, int x1, int y1, int x2, int y2) {
    // Calculate differences
    int dx = x2 - x1;
    int dy = y2 - y1;
    
    // Calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    
    // Calculate increment in x & y for each step
    float xIncrement = (float)dx / (float)steps;
    float yIncrement = (float)dy / (float)steps;
    
    // Put pixel for each step
    float x = x1;
    float y = y1;
    
    printf("\n=== DDA Algorithm Details ===\n");
    printf("From: (%d, %d) to (%d, %d)\n", x1, y1, x2, y2);
    printf("dx = %d, dy = %d\n", dx, dy);
    printf("Steps = %d\n", steps);
    printf("x increment = %.4f\n", xIncrement);
    printf("y increment = %.4f\n", yIncrement);
    printf("===========================\n");
    
    // Draw each point
    for (int i = 0; i <= steps; i++) {
        SDL_RenderDrawPoint(renderer, (int)round(x), (int)round(y));
        x += xIncrement;
        y += yIncrement;
    }
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    
    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "DDA Line Drawing Algorithm",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    printf("\n╔═══════════════════════════════════════════════╗\n");
    printf("║  DDA Line Drawing - Graphics Window          ║\n");
    printf("╚═══════════════════════════════════════════════╝\n");
    printf("\nWindow opened! Drawing lines...\n");
    
    // Main loop flag
    int quit = 0;
    SDL_Event e;
    
    // Clear screen with white background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    // Draw multiple lines in different colors to demonstrate DDA
    
    // Red line - horizontal
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    drawLineDDA(renderer, 100, 100, 700, 100);
    
    // Green line - vertical
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    drawLineDDA(renderer, 400, 50, 400, 550);
    
    // Blue line - diagonal (positive slope)
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    drawLineDDA(renderer, 100, 150, 700, 500);
    
    // Magenta line - diagonal (negative slope)
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    drawLineDDA(renderer, 100, 500, 700, 150);
    
    // Cyan line - shallow slope
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    drawLineDDA(renderer, 50, 300, 750, 350);
    
    // Yellow line - steep slope
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    drawLineDDA(renderer, 200, 50, 250, 550);
    
    // Black line - another diagonal
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    drawLineDDA(renderer, 50, 50, 750, 550);
    
    // Update screen
    SDL_RenderPresent(renderer);
    
    printf("\n✓ Lines drawn successfully!\n");
    printf("\nControls:\n");
    printf("  - Press ESC or close window to exit\n");
    printf("  - Window will stay open until you close it\n\n");
    
    // Main event loop
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            // Check for ESC key
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = 1;
                }
            }
        }
        
        // Small delay to reduce CPU usage
        SDL_Delay(10);
    }
    
    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    printf("Program ended.\n");
    return 0;
}

