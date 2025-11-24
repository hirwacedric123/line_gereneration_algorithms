# Computer Graphics Algorithms - Complete Guide

A comprehensive collection of fundamental line and circle drawing algorithms implemented in C with SDL2 graphics library.

---

## 📁 Table of Contents

1. [Overview](#overview)
2. [Installation](#installation)
3. [Programs Available](#programs-available)
4. [Algorithm 1: DDA Line Drawing](#algorithm-1-dda-line-drawing)
5. [Algorithm 2: Bresenham Line Drawing](#algorithm-2-bresenham-line-drawing)
6. [Algorithm 3: Bresenham Circle Drawing](#algorithm-3-bresenham-circle-drawing)
7. [Quick Reference](#quick-reference)
8. [Compilation](#compilation)

---

## Overview

This repository contains three fundamental computer graphics algorithms:
- **DDA (Digital Differential Analyzer)** - Line drawing using floating-point arithmetic
- **Bresenham's Line Algorithm** - Efficient integer-only line drawing
- **Bresenham's Circle Algorithm** - Efficient integer-only circle drawing with 8-way symmetry

All programs feature:
- ✅ User input for coordinates
- ✅ Real-time graphical display using SDL2
- ✅ Step-by-step calculation output
- ✅ Visual markers for start/end points
- ✅ Detailed algorithm explanations

---

## Installation

### Prerequisites
```bash
sudo apt update
sudo apt install libsdl2-dev gcc make
```

### Compile All Programs
```bash
cd "/mnt/data/UR/graphic design"
gcc -o dda_single_line dda_single_line.c -lSDL2 -lm
gcc -o bresenham_line bresenham_line.c -lSDL2 -lm
gcc -o bresenham_circle bresenham_circle.c -lSDL2 -lm
```

---

## Programs Available

| Program | File | Algorithm | Output Color |
|---------|------|-----------|--------------|
| `./dda_single_line` | `dda_single_line.c` | DDA Line | Black ⚫ |
| `./bresenham_line` | `bresenham_line.c` | Bresenham Line | Blue 🔵 |
| `./bresenham_circle` | `bresenham_circle.c` | Bresenham Circle | Red 🔴 |

---

## Algorithm 1: DDA Line Drawing

### Description
The **Digital Differential Analyzer (DDA)** algorithm draws lines by calculating incremental values and plotting pixels at each step using floating-point arithmetic.

### Mathematical Formulas

#### 1. Calculate Differences
```
dx = x₂ - x₁
dy = y₂ - y₁
```

#### 2. Determine Number of Steps
```
steps = max(|dx|, |dy|)
```

#### 3. Calculate Increments (Floating Point)
```
x_increment = dx / steps
y_increment = dy / steps
```

#### 4. Plot Points
```
x = x₁
y = y₁

for i = 0 to steps:
    plot(round(x), round(y))
    x = x + x_increment
    y = y + y_increment
```

### Code Implementation

```c
void drawLineDDA(int x1, int y1, int x2, int y2) {
    // Step 1: Calculate differences
    int dx = x2 - x1;
    int dy = y2 - y1;
    
    // Step 2: Calculate steps required
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    
    // Step 3: Calculate increment in x & y for each step
    float xIncrement = (float)dx / (float)steps;
    float yIncrement = (float)dy / (float)steps;
    
    // Step 4: Put pixel for each step
    float x = x1;
    float y = y1;
    
    for (int i = 0; i <= steps; i++) {
        setPixel((int)round(x), (int)round(y));
        x += xIncrement;
        y += yIncrement;
    }
}
```

### Example Calculation

**Input:** Line from (100, 100) to (700, 500)

```
Step 1: Calculate differences
  dx = 700 - 100 = 600
  dy = 500 - 100 = 400

Step 2: Determine steps
  steps = max(|600|, |400|) = 600

Step 3: Calculate increments
  x_increment = 600 / 600 = 1.0000
  y_increment = 400 / 600 = 0.6667

Step 4: Plot points
  i=0:  (100.0000, 100.0000) → plot(100, 100)
  i=1:  (101.0000, 100.6667) → plot(101, 101)
  i=2:  (102.0000, 101.3333) → plot(102, 101)
  i=3:  (103.0000, 102.0000) → plot(103, 102)
  ...and so on for 600 steps
```

### Characteristics

| Feature | Value |
|---------|-------|
| **Arithmetic Type** | Floating-point |
| **Speed** | Moderate (slower due to float operations) |
| **Accuracy** | Good (small rounding errors) |
| **Complexity** | O(max(dx, dy)) |
| **Memory** | O(1) |
| **Best For** | Learning, simple implementations |

### Advantages
✅ Simple concept and implementation  
✅ Easy to understand  
✅ Works for all line slopes  

### Disadvantages
❌ Uses floating-point arithmetic (slower)  
❌ Requires rounding at each step  
❌ Potential accumulation of rounding errors  

### How to Run
```bash
./dda_single_line
# Enter: x1, y1, x2, y2
# Example: 100 100 700 500
```

---

## Algorithm 2: Bresenham Line Drawing

### Description
**Bresenham's Line Algorithm** is an efficient method that uses only integer arithmetic to draw lines, making it much faster than DDA.

### Mathematical Formulas

#### 1. Calculate Absolute Differences
```
dx = |x₂ - x₁|
dy = |y₂ - y₁|
```

#### 2. Determine Step Directions
```
sx = (x₁ < x₂) ? 1 : -1
sy = (y₁ < y₂) ? 1 : -1
```

#### 3. Initialize Error Term
```
err = dx - dy
```

#### 4. Bresenham Loop
```
while (true):
    plot(x, y)
    
    if (x == x₂ AND y == y₂):
        break
    
    e2 = 2 × err
    
    if (e2 > -dy):
        err = err - dy
        x = x + sx
    
    if (e2 < dx):
        err = err + dx
        y = y + sy
```

### Code Implementation

```c
void drawLineBresenham(int x1, int y1, int x2, int y2) {
    // Step 1: Calculate absolute differences
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    
    // Step 2: Determine step directions
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    
    // Step 3: Initialize error term
    int err = dx - dy;
    int e2;
    
    int x = x1;
    int y = y1;
    
    // Step 4: Main loop
    while (1) {
        setPixel(x, y);
        
        if (x == x2 && y == y2) {
            break;
        }
        
        e2 = 2 * err;
        
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}
```

### Example Calculation

**Input:** Line from (100, 100) to (105, 103)

```
Step 1: Calculate differences
  dx = |105 - 100| = 5
  dy = |103 - 100| = 3

Step 2: Determine directions
  sx = (100 < 105) ? 1 : -1 = 1
  sy = (100 < 103) ? 1 : -1 = 1

Step 3: Initialize error
  err = 5 - 3 = 2

Step 4: Main loop
  Iteration 0:
    plot(100, 100)
    e2 = 2 × 2 = 4
    e2 > -dy(3)? YES → err = 2 - 3 = -1, x = 101
    e2 < dx(5)?  YES → err = -1 + 5 = 4, y = 101

  Iteration 1:
    plot(101, 101)
    e2 = 2 × 4 = 8
    e2 > -dy(3)? YES → err = 4 - 3 = 1, x = 102
    e2 < dx(5)?  NO
    
  Iteration 2:
    plot(102, 101)
    e2 = 2 × 1 = 2
    e2 > -dy(3)? YES → err = 1 - 3 = -2, x = 103
    e2 < dx(5)?  YES → err = -2 + 5 = 3, y = 102

  ...continues until (105, 103)
```

### Characteristics

| Feature | Value |
|---------|-------|
| **Arithmetic Type** | Integer-only |
| **Speed** | Fast (2-3x faster than DDA) |
| **Accuracy** | Exact (no rounding errors) |
| **Complexity** | O(max(dx, dy)) |
| **Memory** | O(1) |
| **Best For** | Production, performance-critical apps |

### Advantages
✅ Uses only integer arithmetic (very fast)  
✅ No rounding needed  
✅ Pixel-perfect accuracy  
✅ Industry standard  
✅ Hardware-friendly  

### Disadvantages
❌ Slightly more complex to understand  
❌ Requires understanding of error accumulation  

### How to Run
```bash
./bresenham_line
# Enter: x1, y1, x2, y2
# Example: 100 100 700 500
```

---

## Algorithm 3: Bresenham Circle Drawing

### Description
**Bresenham's Circle Algorithm** (also known as **Midpoint Circle Algorithm**) efficiently draws circles using integer arithmetic and 8-way symmetry.

### Mathematical Formulas

#### 1. Initialize Parameters
```
x = 0
y = r (radius)
d = 3 - 2r (initial decision parameter)
```

#### 2. 8-Way Symmetry Points
For each calculated point (x, y), plot 8 symmetrical points:
```
(xc + x, yc + y)    (xc - x, yc + y)
(xc + x, yc - y)    (xc - x, yc - y)
(xc + y, yc + x)    (xc - y, yc + x)
(xc + y, yc - x)    (xc - y, yc - x)
```

#### 3. Decision Parameter Update
```
while (x ≤ y):
    plot 8 symmetrical points
    
    x = x + 1
    
    if (d < 0):
        d = d + 4x + 6           // East point
    else:
        y = y - 1
        d = d + 4(x - y) + 10    // South-East point
```

### Detailed Formula Derivation

The decision parameter is based on the circle equation:
```
x² + y² = r²
```

At each step, we evaluate:
```
d = (x + 1)² + (y - 0.5)² - r²
```

For integer approximation:
```
Initial: d₀ = 3 - 2r

If d < 0 (choose E):
  d_{k+1} = d_k + 4x + 6

If d ≥ 0 (choose SE):
  d_{k+1} = d_k + 4(x - y) + 10
```

### Code Implementation

```c
void plotCirclePoints(int xc, int yc, int x, int y) {
    // Plot 8 symmetrical points
    setPixel(xc + x, yc + y);  // Octant 1
    setPixel(xc - x, yc + y);  // Octant 2
    setPixel(xc + x, yc - y);  // Octant 3
    setPixel(xc - x, yc - y);  // Octant 4
    setPixel(xc + y, yc + x);  // Octant 5
    setPixel(xc - y, yc + x);  // Octant 6
    setPixel(xc + y, yc - x);  // Octant 7
    setPixel(xc - y, yc - x);  // Octant 8
}

void drawCircleBresenham(int xc, int yc, int radius) {
    // Step 1: Initialize
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;
    
    // Step 2: Plot initial points
    plotCirclePoints(xc, yc, x, y);
    
    // Step 3: Main loop
    while (x <= y) {
        x++;
        
        // Update decision parameter
        if (d < 0) {
            // Choose East point
            d = d + 4 * x + 6;
        } else {
            // Choose South-East point
            y--;
            d = d + 4 * (x - y) + 10;
        }
        
        // Plot 8 symmetrical points
        plotCirclePoints(xc, yc, x, y);
    }
}
```

### Example Calculation

**Input:** Circle at center (400, 300) with radius = 10

```
Step 1: Initialize
  x = 0
  y = 10
  d = 3 - 2(10) = 3 - 20 = -17

Step 2: Initial plot
  Plot 8 points for (0, 10):
    (400+0, 300+10) = (400, 310)
    (400-0, 300+10) = (400, 310) [duplicate]
    (400+0, 300-10) = (400, 290)
    (400-0, 300-10) = (400, 290) [duplicate]
    (400+10, 300+0) = (410, 300)
    (400-10, 300+0) = (390, 300)
    (400+10, 300-0) = (410, 300) [duplicate]
    (400-10, 300-0) = (390, 300) [duplicate]

Step 3: Main loop

  Iteration 1:
    x = 1
    d = -17 (< 0, choose E)
    d = -17 + 4(1) + 6 = -17 + 4 + 6 = -7
    Plot 8 points for (1, 10)

  Iteration 2:
    x = 2
    d = -7 (< 0, choose E)
    d = -7 + 4(2) + 6 = -7 + 8 + 6 = 7
    Plot 8 points for (2, 10)

  Iteration 3:
    x = 3
    d = 7 (≥ 0, choose SE)
    y = 9
    d = 7 + 4(3 - 9) + 10 = 7 + 4(-6) + 10 = 7 - 24 + 10 = -7
    Plot 8 points for (3, 9)

  Iteration 4:
    x = 4
    d = -7 (< 0, choose E)
    d = -7 + 4(4) + 6 = -7 + 16 + 6 = 15
    Plot 8 points for (4, 9)

  Iteration 5:
    x = 5
    d = 15 (≥ 0, choose SE)
    y = 8
    d = 15 + 4(5 - 8) + 10 = 15 + 4(-3) + 10 = 15 - 12 + 10 = 13
    Plot 8 points for (5, 8)

  Iteration 6:
    x = 6
    d = 13 (≥ 0, choose SE)
    y = 7
    d = 13 + 4(6 - 7) + 10 = 13 + 4(-1) + 10 = 13 - 4 + 10 = 19
    Plot 8 points for (6, 7)

  Iteration 7:
    x = 7
    d = 19 (≥ 0, choose SE)
    y = 6
    d = 19 + 4(7 - 6) + 10 = 19 + 4(1) + 10 = 19 + 4 + 10 = 33
    Plot 8 points for (7, 6)
    
    x = 7, y = 6, x > y? NO, continue

  Iteration 8:
    x = 8 > y = 6, STOP

  Total: 8 octant points calculated
  Total pixels plotted: 8 × 8 = 64 pixels (approximately)
```

### Characteristics

| Feature | Value |
|---------|-------|
| **Arithmetic Type** | Integer-only |
| **Speed** | Very fast (uses symmetry) |
| **Accuracy** | Exact (pixel-perfect circles) |
| **Complexity** | O(r) - only r/√2 calculations |
| **Memory** | O(1) |
| **Symmetry** | 8-way (1 calculation → 8 pixels) |
| **Best For** | All circle drawing needs |

### Advantages
✅ Integer-only arithmetic (very fast)  
✅ 8-way symmetry (only 1/8 of circle calculated)  
✅ Pixel-perfect accuracy  
✅ Minimal calculations per pixel  
✅ Hardware-friendly  

### Disadvantages
❌ Circle-specific (doesn't extend to ellipses easily)  
❌ Slightly complex to understand initially  

### How to Run
```bash
./bresenham_circle
# Enter: xc (center x), yc (center y), radius
# Example: 400 300 150
```

---

## Quick Reference

### Formula Summary

#### DDA Line Algorithm
```
dx = x₂ - x₁
dy = y₂ - y₁
steps = max(|dx|, |dy|)
x_inc = dx / steps  (float)
y_inc = dy / steps  (float)

for i = 0 to steps:
    plot(round(x), round(y))
    x += x_inc
    y += y_inc
```

#### Bresenham Line Algorithm
```
dx = |x₂ - x₁|
dy = |y₂ - y₁|
sx = (x₁ < x₂) ? 1 : -1
sy = (y₁ < y₂) ? 1 : -1
err = dx - dy

while not at end:
    plot(x, y)
    e2 = 2 × err
    if e2 > -dy: err -= dy, x += sx
    if e2 < dx: err += dx, y += sy
```

#### Bresenham Circle Algorithm
```
x = 0
y = r
d = 3 - 2r

while x ≤ y:
    plot 8 symmetrical points (x,y)
    x++
    if d < 0: d = d + 4x + 6
    else: y--, d = d + 4(x-y) + 10
```

### Comparison Table

| Feature | DDA Line | Bresenham Line | Bresenham Circle |
|---------|----------|----------------|------------------|
| **Input** | x₁,y₁,x₂,y₂ | x₁,y₁,x₂,y₂ | xc,yc,r |
| **Arithmetic** | Float | Integer | Integer |
| **Speed** | Moderate | Fast | Very Fast |
| **Symmetry** | None | None | 8-way |
| **Color** | Black ⚫ | Blue 🔵 | Red 🔴 |
| **Use Case** | Learning | Production | Production |

### Sample Test Inputs

**Lines (DDA & Bresenham):**
```
Horizontal:  x1=100  y1=300  x2=700  y2=300
Vertical:    x1=400  y1=50   x2=400  y2=550
Diagonal:    x1=100  y1=100  x2=700  y2=500
Steep:       x1=400  y1=100  x2=450  y2=500
```

**Circles (Bresenham):**
```
Small:       xc=400  yc=300  radius=50
Medium:      xc=400  yc=300  radius=150
Large:       xc=400  yc=300  radius=250
```

---

## Compilation

### Individual Programs
```bash
gcc -o dda_single_line dda_single_line.c -lSDL2 -lm
gcc -o bresenham_line bresenham_line.c -lSDL2 -lm
gcc -o bresenham_circle bresenham_circle.c -lSDL2 -lm
```

### All at Once
```bash
gcc -o dda_single_line dda_single_line.c -lSDL2 -lm && \
gcc -o bresenham_line bresenham_line.c -lSDL2 -lm && \
gcc -o bresenham_circle bresenham_circle.c -lSDL2 -lm && \
echo "✓ All programs compiled successfully!"
```

### Compiler Flags Explained
- `-o <name>` - Output executable name
- `-lSDL2` - Link SDL2 library (graphics)
- `-lm` - Link math library (for abs, round functions)

---

## Window Controls

All programs support:
- **ESC key** - Close window and exit
- **X button** - Close window and exit

---

## Visual Markers

### DDA Line
- 🔴 Red dot = Start point (x₁, y₁)
- ⚫ Black line = Line path
- 🟢 Green dot = End point (x₂, y₂)

### Bresenham Line
- 🔴 Red dot = Start point (x₁, y₁)
- 🔵 Blue line = Line path
- 🟢 Green dot = End point (x₂, y₂)

### Bresenham Circle
- 🔴 Red circle = Circle outline
- 🔵 Blue cross = Center point (xc, yc)

---

## Troubleshooting

### SDL2 not found
```bash
sudo apt install libsdl2-dev
```

### Permission denied
```bash
chmod +x dda_single_line bresenham_line bresenham_circle
```

### Coordinates out of range
Valid range: x (0-799), y (0-599)

---

## Additional Resources

- `ALGORITHM_COMPARISON.md` - Detailed comparison of DDA vs Bresenham
- `CIRCLE_ALGORITHM.md` - In-depth circle algorithm guide
- `ALL_ALGORITHMS.txt` - Quick reference for all programs
- `GRAPHICS_SETUP.md` - SDL2 installation and setup guide

---

## Author

Computer Graphics Algorithms Implementation  
Educational purposes - Computer Graphics Course

---

## License

Free to use for educational purposes.

---

**Happy Graphics Programming! 🎨**
