#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Bresenham's Line Drawing Algorithm
void drawLineBresenham(SDL_Renderer* renderer, int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    
    int sx = (x1 < x2) ? 1 : -1;  // Step direction for x
    int sy = (y1 < y2) ? 1 : -1;  // Step direction for y
    
    int err = dx - dy;  // Initial error term
    int e2;
    
    int x = x1;
    int y = y1;
    
    // Display Bresenham algorithm details
    printf("\n╔════════════════════════════════════════════════════╗\n");
    printf("║    Bresenham's Algorithm Calculation Details      ║\n");
    printf("╚════════════════════════════════════════════════════╝\n");
    printf("  Starting Point (x1, y1) : (%d, %d)\n", x1, y1);
    printf("  Ending Point   (x2, y2) : (%d, %d)\n", x2, y2);
    printf("  ────────────────────────────────────────────────────\n");
    printf("  dx = |x2 - x1| = |%d - %d| = %d\n", x2, x1, dx);
    printf("  dy = |y2 - y1| = |%d - %d| = %d\n", y2, y1, dy);
    printf("  ────────────────────────────────────────────────────\n");
    printf("  sx (x step direction) = %d\n", sx);
    printf("  sy (y step direction) = %d\n", sy);
    printf("  ────────────────────────────────────────────────────\n");
    printf("  Initial error = dx - dy = %d - %d = %d\n", dx, dy, err);
    printf("╚════════════════════════════════════════════════════╝\n\n");
    
    int pixelCount = 0;
    
    // Main loop - draw line pixel by pixel
    while (1) {
        // Plot current point
        SDL_RenderDrawPoint(renderer, x, y);
        pixelCount++;
        
        // Check if we've reached the end point
        if (x == x2 && y == y2) {
            break;
        }
        
        e2 = 2 * err;
        
        // Move in x direction
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        
        // Move in y direction
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
    
    printf("✓ Line drawn successfully!\n");
    printf("  Total pixels plotted: %d\n", pixelCount);
}

int main(int argc, char* argv[]) {
    int x1, y1, x2, y2;
    
    printf("\n");
    printf("╔══════════════════════════════════════════════════════╗\n");
    printf("║     Bresenham's Line Generation Algorithm           ║\n");
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
        "Bresenham's Line Algorithm",
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
    
    // Set drawing color to blue for Bresenham line
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    
    // Draw the line using Bresenham's algorithm
    drawLineBresenham(renderer, x1, y1, x2, y2);
    
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
    printf("  🔵 Blue line = Your Bresenham line\n");
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

