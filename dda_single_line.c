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
    
    // Starting point
    float x = x1;
    float y = y1;
    
    // Display DDA algorithm details
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║    DDA Algorithm Calculation Details      ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    printf("  Starting Point (x1, y1) : (%d, %d)\n", x1, y1);
    printf("  Ending Point   (x2, y2) : (%d, %d)\n", x2, y2);
    printf("  ──────────────────────────────────────────\n");
    printf("  dx = x2 - x1 = %d - %d = %d\n", x2, x1, dx);
    printf("  dy = y2 - y1 = %d - %d = %d\n", y2, y1, dy);
    printf("  ──────────────────────────────────────────\n");
    printf("  Steps = max(|dx|, |dy|) = max(%d, %d) = %d\n", abs(dx), abs(dy), steps);
    printf("  ──────────────────────────────────────────\n");
    printf("  x increment = dx/steps = %d/%d = %.4f\n", dx, steps, xIncrement);
    printf("  y increment = dy/steps = %d/%d = %.4f\n", dy, steps, yIncrement);
    printf("╚════════════════════════════════════════════╝\n\n");
    
    // Draw each pixel point
    printf("Drawing %d pixels...\n", steps + 1);
    for (int i = 0; i <= steps; i++) {
        SDL_RenderDrawPoint(renderer, (int)round(x), (int)round(y));
        x += xIncrement;
        y += yIncrement;
    }
    printf("✓ Line drawn successfully!\n");
}

int main(int argc, char* argv[]) {
    int x1, y1, x2, y2;
    
    printf("\n");
    printf("╔══════════════════════════════════════════════════════╗\n");
    printf("║  DDA (Digital Differential Analyzer) Line Drawing   ║\n");
    printf("╚══════════════════════════════════════════════════════╝\n\n");
    
    printf("Window size: %d x %d pixels\n", WINDOW_WIDTH, WINDOW_HEIGHT);
    printf("Valid coordinates: x (0-%d), y (0-%d)\n\n", WINDOW_WIDTH-1, WINDOW_HEIGHT-1);
    
    // Get user input for line coordinates
    printf("Enter the starting point coordinates:\n");
    printf("  x1: ");
    scanf("%d", &x1);
    printf("  y1: ");
    scanf("%d", &y1);
    
    printf("\nEnter the ending point coordinates:\n");
    printf("  x2: ");
    scanf("%d", &x2);
    printf("  y2: ");
    scanf("%d", &y2);
    
    // Validate coordinates
    if (x1 < 0 || x1 >= WINDOW_WIDTH || x2 < 0 || x2 >= WINDOW_WIDTH ||
        y1 < 0 || y1 >= WINDOW_HEIGHT || y2 < 0 || y2 >= WINDOW_HEIGHT) {
        printf("\n⚠ ERROR: Coordinates must be within window bounds!\n");
        printf("   x: 0 to %d\n", WINDOW_WIDTH-1);
        printf("   y: 0 to %d\n", WINDOW_HEIGHT-1);
        return 1;
    }
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("\n✗ SDL initialization failed: %s\n", SDL_GetError());
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
    
    if (!window) {
        printf("\n✗ Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("\n✗ Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    // Clear screen with white background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    // Set drawing color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    // Draw the line using DDA algorithm
    drawLineDDA(renderer, x1, y1, x2, y2);
    
    // Draw small circles at start and end points for clarity
    // Red circle at starting point
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int dx = -4; dx <= 4; dx++) {
        for (int dy = -4; dy <= 4; dy++) {
            if (dx*dx + dy*dy <= 16) {
                SDL_RenderDrawPoint(renderer, x1 + dx, y1 + dy);
            }
        }
    }
    
    // Green circle at ending point
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int dx = -4; dx <= 4; dx++) {
        for (int dy = -4; dy <= 4; dy++) {
            if (dx*dx + dy*dy <= 16) {
                SDL_RenderDrawPoint(renderer, x2 + dx, y2 + dy);
            }
        }
    }
    
    // Update screen to show the line
    SDL_RenderPresent(renderer);
    
    printf("\n");
    printf("Window opened with your line!\n");
    printf("  🔴 Red dot   = Starting point (%d, %d)\n", x1, y1);
    printf("  ⚫ Black line = Your DDA line\n");
    printf("  🟢 Green dot = Ending point (%d, %d)\n", x2, y2);
    printf("\nPress ESC or close the window to exit.\n");
    
    // Event loop - keep window open until user closes it
    int quit = 0;
    SDL_Event e;
    
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = 1;
                }
            }
        }
        SDL_Delay(10);
    }
    
    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    printf("\nProgram ended. Goodbye!\n\n");
    return 0;
}

