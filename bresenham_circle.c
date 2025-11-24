#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Plot 8 symmetrical points of the circle
void plotCirclePoints(SDL_Renderer* renderer, int xc, int yc, int x, int y) {
    SDL_RenderDrawPoint(renderer, xc + x, yc + y);  // Octant 1
    SDL_RenderDrawPoint(renderer, xc - x, yc + y);  // Octant 2
    SDL_RenderDrawPoint(renderer, xc + x, yc - y);  // Octant 3
    SDL_RenderDrawPoint(renderer, xc - x, yc - y);  // Octant 4
    SDL_RenderDrawPoint(renderer, xc + y, yc + x);  // Octant 5
    SDL_RenderDrawPoint(renderer, xc - y, yc + x);  // Octant 6
    SDL_RenderDrawPoint(renderer, xc + y, yc - x);  // Octant 7
    SDL_RenderDrawPoint(renderer, xc - y, yc - x);  // Octant 8
}

// Bresenham's Circle Drawing Algorithm (Midpoint Circle Algorithm)
void drawCircleBresenham(SDL_Renderer* renderer, int xc, int yc, int radius) {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;  // Initial decision parameter
    
    printf("\n╔════════════════════════════════════════════════════════╗\n");
    printf("║    Bresenham's Circle Algorithm Calculation Details   ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    printf("  Center (xc, yc) : (%d, %d)\n", xc, yc);
    printf("  Radius          : %d\n", radius);
    printf("  ────────────────────────────────────────────────────────\n");
    printf("  Initial decision parameter:\n");
    printf("  d = 3 - 2*r = 3 - 2*%d = %d\n", radius, d);
    printf("  ────────────────────────────────────────────────────────\n");
    printf("  Starting point: (x=0, y=%d)\n", radius);
    printf("╚════════════════════════════════════════════════════════╝\n\n");
    
    printf("Drawing circle using 8-way symmetry:\n");
    printf("  (Each calculated point generates 8 symmetrical points)\n\n");
    
    int step = 0;
    
    // Draw initial point
    plotCirclePoints(renderer, xc, yc, x, y);
    
    printf("Step %2d: x=%3d, y=%3d, d=%4d\n", step++, x, y, d);
    
    // Main loop - calculate one octant, use symmetry for others
    while (x <= y) {
        x++;
        
        if (d < 0) {
            // Select E (East) point
            d = d + 4 * x + 6;
        } else {
            // Select SE (South-East) point
            y--;
            d = d + 4 * (x - y) + 10;
        }
        
        plotCirclePoints(renderer, xc, yc, x, y);
        
        if (step < 10 || x == y) {  // Show first 10 steps and last step
            printf("Step %2d: x=%3d, y=%3d, d=%4d\n", step, x, y, d);
        } else if (step == 10) {
            printf("         ... (calculating remaining points) ...\n");
        }
        step++;
    }
    
    printf("\n✓ Circle drawn successfully!\n");
    printf("  Total steps (octant): %d\n", step);
    printf("  Total pixels plotted: %d (using 8-way symmetry)\n", step * 8);
}

int main(int argc, char* argv[]) {
    int xc, yc, radius;
    
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║     Bresenham's Circle Generation Algorithm             ║\n");
    printf("║     (Midpoint Circle Algorithm)                          ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    printf("Window size: %d x %d pixels\n", WINDOW_WIDTH, WINDOW_HEIGHT);
    printf("Valid center: x (0-%d), y (0-%d)\n\n", WINDOW_WIDTH-1, WINDOW_HEIGHT-1);
    
    // Get user input for circle parameters
    printf("Enter the center coordinates:\n");
    printf("  xc (center x): ");
    scanf("%d", &xc);
    printf("  yc (center y): ");
    scanf("%d", &yc);
    
    printf("\nEnter the radius:\n");
    printf("  radius: ");
    scanf("%d", &radius);
    
    // Validate input
    if (xc < 0 || xc >= WINDOW_WIDTH || yc < 0 || yc >= WINDOW_HEIGHT) {
        printf("\n⚠ ERROR: Center coordinates must be within window bounds!\n");
        printf("   xc: 0 to %d\n", WINDOW_WIDTH-1);
        printf("   yc: 0 to %d\n", WINDOW_HEIGHT-1);
        return 1;
    }
    
    if (radius <= 0) {
        printf("\n⚠ ERROR: Radius must be positive!\n");
        return 1;
    }
    
    if (xc - radius < 0 || xc + radius >= WINDOW_WIDTH ||
        yc - radius < 0 || yc + radius >= WINDOW_HEIGHT) {
        printf("\n⚠ WARNING: Circle extends beyond window boundaries!\n");
        printf("   It will be clipped at the edges.\n\n");
    }
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("\n✗ SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }
    
    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "Bresenham's Circle Algorithm",
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
    
    // Set drawing color to red for circle
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    // Draw the circle using Bresenham's algorithm
    drawCircleBresenham(renderer, xc, yc, radius);
    
    // Draw center point marker (blue cross)
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for (int i = -5; i <= 5; i++) {
        SDL_RenderDrawPoint(renderer, xc + i, yc);      // Horizontal line
        SDL_RenderDrawPoint(renderer, xc, yc + i);      // Vertical line
    }
    
    // Draw small circle at center
    for (int dx = -2; dx <= 2; dx++) {
        for (int dy = -2; dy <= 2; dy++) {
            if (dx*dx + dy*dy <= 4) {
                SDL_RenderDrawPoint(renderer, xc + dx, yc + dy);
            }
        }
    }
    
    // Update screen to show the circle
    SDL_RenderPresent(renderer);
    
    printf("\n");
    printf("Window opened with your circle!\n");
    printf("  🔴 Red circle  = Circle with radius %d\n", radius);
    printf("  🔵 Blue cross  = Center point (%d, %d)\n", xc, yc);
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

