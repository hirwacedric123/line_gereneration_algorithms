#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct {
    unsigned char r, g, b;
} Pixel;

void initImage(Pixel image[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            image[i][j].r = 255;
            image[i][j].g = 255;
            image[i][j].b = 255;
        }
    }
}

void setPixel(Pixel image[HEIGHT][WIDTH], int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        image[y][x].r = r;
        image[y][x].g = g;
        image[y][x].b = b;
    }
}

void drawLineDDA(Pixel image[HEIGHT][WIDTH], int x1, int y1, int x2, int y2, 
                 unsigned char r, unsigned char g, unsigned char b) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    
    float xIncrement = (float)dx / (float)steps;
    float yIncrement = (float)dy / (float)steps;
    
    float x = x1;
    float y = y1;
    
    printf("\n--- DDA Algorithm Details ---\n");
    printf("Starting point: (%d, %d)\n", x1, y1);
    printf("Ending point: (%d, %d)\n", x2, y2);
    printf("dx = %d, dy = %d\n", dx, dy);
    printf("Number of steps = %d\n", steps);
    printf("x increment = %.4f\n", xIncrement);
    printf("y increment = %.4f\n", yIncrement);
    printf("----------------------------\n\n");
    
    for (int i = 0; i <= steps; i++) {
        setPixel(image, (int)round(x), (int)round(y), r, g, b);
        x += xIncrement;
        y += yIncrement;
    }
}

void saveImage(Pixel image[HEIGHT][WIDTH], const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        printf("Error: Could not open file %s for writing\n", filename);
        return;
    }
    
    fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            fwrite(&image[i][j], 3, 1, fp);
        }
    }
    
    fclose(fp);
    printf("✓ Image saved as %s\n", filename);
}

int main() {
    Pixel (*image)[WIDTH] = malloc(sizeof(Pixel) * HEIGHT * WIDTH);
    if (!image) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    initImage(image);
    
    printf("╔═══════════════════════════════════════════════════╗\n");
    printf("║  DDA (Digital Differential Analyzer) Algorithm    ║\n");
    printf("║  Line Drawing Program                             ║\n");
    printf("╚═══════════════════════════════════════════════════╝\n\n");
    
    printf("Image dimensions: %d x %d pixels\n\n", WIDTH, HEIGHT);
    
    int x1, y1, x2, y2;
    char choice;
    
    do {
        printf("Enter starting point (x1 y1): ");
        scanf("%d %d", &x1, &y1);
        
        printf("Enter ending point (x2 y2): ");
        scanf("%d %d", &x2, &y2);
        
        // Validate input
        if (x1 < 0 || x1 >= WIDTH || x2 < 0 || x2 >= WIDTH ||
            y1 < 0 || y1 >= HEIGHT || y2 < 0 || y2 >= HEIGHT) {
            printf("\n⚠ Warning: Coordinates should be within range:\n");
            printf("  x: 0 to %d\n", WIDTH-1);
            printf("  y: 0 to %d\n\n", HEIGHT-1);
        }
        
        // Draw the line (in red)
        drawLineDDA(image, x1, y1, x2, y2, 255, 0, 0);
        
        printf("Do you want to draw another line? (y/n): ");
        scanf(" %c", &choice);
        printf("\n");
        
    } while (choice == 'y' || choice == 'Y');
    
    saveImage(image, "my_lines.ppm");
    
    printf("\nTo view your image, use:\n");
    printf("  eog my_lines.ppm\n");
    printf("Or convert to PNG:\n");
    printf("  convert my_lines.ppm my_lines.png\n\n");
    
    free(image);
    return 0;
}

