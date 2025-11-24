# Formula Locations in Code Files

This document shows exactly where each mathematical formula is implemented in your C code files.

---

## 📁 File 1: `dda_single_line.c` (182 lines)

### DDA Line Drawing Algorithm

#### Function: `drawLineDDA()` - Lines 10-50

**Formula 1: Calculate Differences (Lines 12-13)**
```c
12|    int dx = x2 - x1;
13|    int dy = y2 - y1;
```
📐 **Mathematical Formula:** `dx = x₂ - x₁`, `dy = y₂ - y₁`

---

**Formula 2: Calculate Steps (Line 16)**
```c
16|    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
```
📐 **Mathematical Formula:** `steps = max(|dx|, |dy|)`

---

**Formula 3: Calculate Increments - FLOATING POINT (Lines 19-20)**
```c
19|    float xIncrement = (float)dx / (float)steps;
20|    float yIncrement = (float)dy / (float)steps;
```
📐 **Mathematical Formula:** 
- `x_increment = dx / steps` (floating point division)
- `y_increment = dy / steps` (floating point division)

---

**Formula 4: Initialize Starting Point (Lines 23-24)**
```c
23|    float x = x1;
24|    float y = y1;
```
📐 **Mathematical Formula:** `x = x₁`, `y = y₁`

---

**Formula 5: DDA Main Loop (Lines 44-48)**
```c
44|    for (int i = 0; i <= steps; i++) {
45|        SDL_RenderDrawPoint(renderer, (int)round(x), (int)round(y));
46|        x += xIncrement;
47|        y += yIncrement;
48|    }
```
📐 **Mathematical Formula:**
```
for i = 0 to steps:
    plot(round(x), round(y))
    x = x + x_increment
    y = y + y_increment
```

---

### Summary of DDA Formulas in Code

| Line | Formula | Description |
|------|---------|-------------|
| 12 | `dx = x2 - x1` | X difference |
| 13 | `dy = y2 - y1` | Y difference |
| 16 | `steps = max(abs(dx), abs(dy))` | Number of steps |
| 19 | `xIncrement = dx / steps` | X increment (float) |
| 20 | `yIncrement = dy / steps` | Y increment (float) |
| 44-48 | Main DDA loop | Iterative plotting |
| 45 | `round(x), round(y)` | Rounding for pixel coords |
| 46-47 | `x += xIncrement`, `y += yIncrement` | Increment updates |

---

## 📁 File 2: `bresenham_line.c` (201 lines)

### Bresenham Line Drawing Algorithm

#### Function: `drawLineBresenham()` - Lines 10-69

**Formula 1: Calculate Absolute Differences (Lines 11-12)**
```c
11|    int dx = abs(x2 - x1);
12|    int dy = abs(y2 - y1);
```
📐 **Mathematical Formula:** `dx = |x₂ - x₁|`, `dy = |y₂ - y₁|`

---

**Formula 2: Determine Step Directions (Lines 14-15)**
```c
14|    int sx = (x1 < x2) ? 1 : -1;  // Step direction for x
15|    int sy = (y1 < y2) ? 1 : -1;  // Step direction for y
```
📐 **Mathematical Formula:**
- `sx = (x₁ < x₂) ? 1 : -1`
- `sy = (y₁ < y₂) ? 1 : -1`

---

**Formula 3: Initialize Error Term (Line 17)**
```c
17|    int err = dx - dy;  // Initial error term
```
📐 **Mathematical Formula:** `err = dx - dy`

---

**Formula 4: Bresenham Main Loop (Lines 42-65)**
```c
42|    while (1) {
43|        // Plot current point
44|        SDL_RenderDrawPoint(renderer, x, y);
45|        pixelCount++;
46|        
47|        // Check if we've reached the end point
48|        if (x == x2 && y == y2) {
49|            break;
50|        }
51|        
52|        e2 = 2 * err;
53|        
54|        // Move in x direction
55|        if (e2 > -dy) {
56|            err -= dy;
57|            x += sx;
58|        }
59|        
60|        // Move in y direction
61|        if (e2 < dx) {
62|            err += dx;
63|            y += sy;
64|        }
65|    }
```

📐 **Mathematical Formula:**
```
while not at end:
    plot(x, y)
    e2 = 2 × err
    
    if e2 > -dy:
        err = err - dy
        x = x + sx
    
    if e2 < dx:
        err = err + dx
        y = y + sy
```

---

### Detailed Formula Breakdown

| Line | Formula | Description |
|------|---------|-------------|
| 11 | `dx = abs(x2 - x1)` | Absolute X difference |
| 12 | `dy = abs(y2 - y1)` | Absolute Y difference |
| 14 | `sx = (x1 < x2) ? 1 : -1` | X direction (+1 or -1) |
| 15 | `sy = (y1 < y2) ? 1 : -1` | Y direction (+1 or -1) |
| 17 | `err = dx - dy` | Initial error parameter |
| 52 | `e2 = 2 * err` | Double the error |
| 55 | `if (e2 > -dy)` | Check error vs -dy |
| 56 | `err -= dy` | Update error (E move) |
| 57 | `x += sx` | Move in X direction |
| 61 | `if (e2 < dx)` | Check error vs dx |
| 62 | `err += dx` | Update error (S move) |
| 63 | `y += sy` | Move in Y direction |

---

## 📁 File 3: `bresenham_circle.c` (211 lines)

### Bresenham Circle Drawing Algorithm (Midpoint Circle)

#### Function: `plotCirclePoints()` - Lines 9-18

**Formula: 8-Way Symmetry Points (Lines 10-17)**
```c
10|    SDL_RenderDrawPoint(renderer, xc + x, yc + y);  // Octant 1
11|    SDL_RenderDrawPoint(renderer, xc - x, yc + y);  // Octant 2
12|    SDL_RenderDrawPoint(renderer, xc + x, yc - y);  // Octant 3
13|    SDL_RenderDrawPoint(renderer, xc - x, yc - y);  // Octant 4
14|    SDL_RenderDrawPoint(renderer, xc + y, yc + x);  // Octant 5
15|    SDL_RenderDrawPoint(renderer, xc - y, yc + x);  // Octant 6
16|    SDL_RenderDrawPoint(renderer, xc + y, yc - x);  // Octant 7
17|    SDL_RenderDrawPoint(renderer, xc - y, yc - x);  // Octant 8
```

📐 **Mathematical Formula:** For each point (x, y), plot 8 symmetrical points:
```
(xc + x, yc + y)    (xc - x, yc + y)
(xc + x, yc - y)    (xc - x, yc - y)
(xc + y, yc + x)    (xc - y, yc + x)
(xc + y, yc - x)    (xc - y, yc - x)
```

---

#### Function: `drawCircleBresenham()` - Lines 21-74

**Formula 1: Initialize Parameters (Lines 22-24)**
```c
22|    int x = 0;
23|    int y = radius;
24|    int d = 3 - 2 * radius;  // Initial decision parameter
```
📐 **Mathematical Formula:**
- `x = 0`
- `y = r`
- `d = 3 - 2r` (initial decision parameter)

---

**Formula 2: Bresenham Circle Main Loop (Lines 49-69)**
```c
49|    while (x <= y) {
50|        x++;
51|        
52|        if (d < 0) {
53|            // Select E (East) point
54|            d = d + 4 * x + 6;
55|        } else {
56|            // Select SE (South-East) point
57|            y--;
58|            d = d + 4 * (x - y) + 10;
59|        }
60|        
61|        plotCirclePoints(renderer, xc, yc, x, y);
62|        
63|        if (step < 10 || x == y) {  // Show first 10 steps and last step
64|            printf("Step %2d: x=%3d, y=%3d, d=%4d\n", step, x, y, d);
65|        } else if (step == 10) {
66|            printf("         ... (calculating remaining points) ...\n");
67|        }
68|        step++;
69|    }
```

📐 **Mathematical Formula:**
```
while x ≤ y:
    x = x + 1
    
    if d < 0:
        d = d + 4x + 6           (choose East point)
    else:
        y = y - 1
        d = d + 4(x - y) + 10    (choose South-East point)
    
    plot 8 symmetrical points
```

---

### Detailed Formula Breakdown

| Line | Formula | Description |
|------|---------|-------------|
| 22 | `x = 0` | Starting X coordinate |
| 23 | `y = radius` | Starting Y coordinate |
| 24 | `d = 3 - 2 * radius` | Initial decision parameter |
| 10-17 | 8 plot statements | 8-way symmetry implementation |
| 49 | `while (x <= y)` | Loop condition (one octant) |
| 50 | `x++` | Increment X |
| 52 | `if (d < 0)` | Decision: E or SE |
| 54 | `d = d + 4 * x + 6` | Update d (East move) |
| 57 | `y--` | Decrement Y |
| 58 | `d = d + 4 * (x - y) + 10` | Update d (SE move) |
| 61 | `plotCirclePoints()` | Plot 8 symmetrical points |

---

## 📊 Quick Formula Reference by File

### dda_single_line.c
```
Lines 12-13:  dx = x₂-x₁, dy = y₂-y₁
Line 16:      steps = max(|dx|, |dy|)
Lines 19-20:  x_inc = dx/steps, y_inc = dy/steps (FLOATS)
Lines 44-48:  Main DDA loop with rounding
```

### bresenham_line.c
```
Lines 11-12:  dx = |x₂-x₁|, dy = |y₂-y₁|
Lines 14-15:  sx, sy = ±1 (directions)
Line 17:      err = dx - dy
Line 52:      e2 = 2 × err
Lines 55-58:  if e2 > -dy: err -= dy, x += sx
Lines 61-64:  if e2 < dx: err += dx, y += sy
```

### bresenham_circle.c
```
Lines 22-24:  x=0, y=r, d=3-2r
Lines 10-17:  8 symmetry points (xc±x, yc±y) and (xc±y, yc±x)
Line 54:      if d<0: d = d + 4x + 6
Line 58:      if d≥0: d = d + 4(x-y) + 10, y--
```

---

## 🔍 How to Find Formulas in Your Code

### Method 1: Using grep
```bash
# Find all formula calculations
grep -n "dx = " *.c
grep -n "dy = " *.c
grep -n "steps = " *.c
grep -n "Increment" *.c
grep -n "err" *.c
grep -n "decision" *.c
```

### Method 2: Using line numbers
```bash
# View specific lines
sed -n '12,20p' dda_single_line.c      # DDA formulas
sed -n '11,17p' bresenham_line.c       # Bresenham line init
sed -n '22,24p' bresenham_circle.c     # Bresenham circle init
```

### Method 3: Search in editor
Open files and search for:
- `dx` - Find difference calculations
- `increment` - Find DDA increments
- `err` - Find Bresenham error terms
- `decision` - Find circle decision parameter

---

## 📚 Formula Categories

### Initialization Formulas
| Algorithm | File | Lines | Formula |
|-----------|------|-------|---------|
| DDA | dda_single_line.c | 12-13 | `dx = x₂-x₁`, `dy = y₂-y₁` |
| DDA | dda_single_line.c | 16 | `steps = max(\|dx\|, \|dy\|)` |
| Bresenham Line | bresenham_line.c | 11-12 | `dx = \|x₂-x₁\|`, `dy = \|y₂-y₁\|` |
| Bresenham Line | bresenham_line.c | 14-15 | `sx = ±1`, `sy = ±1` |
| Bresenham Circle | bresenham_circle.c | 22-24 | `x=0`, `y=r`, `d=3-2r` |

### Loop/Update Formulas
| Algorithm | File | Lines | Formula |
|-----------|------|-------|---------|
| DDA | dda_single_line.c | 46-47 | `x += x_inc`, `y += y_inc` |
| Bresenham Line | bresenham_line.c | 52-64 | Error-based updates |
| Bresenham Circle | bresenham_circle.c | 54, 58 | `d += 4x+6` or `d += 4(x-y)+10` |

### Symmetry Formulas
| Algorithm | File | Lines | Formula |
|-----------|------|-------|---------|
| Bresenham Circle | bresenham_circle.c | 10-17 | 8-way symmetry points |

---

## 💡 Tips for Understanding the Code

1. **DDA Algorithm** - Look for `float` variables and division operations
2. **Bresenham Algorithms** - Look for `int` variables and error terms
3. **Circle Symmetry** - Look for multiple plot statements with ± signs
4. **Main Loops** - Start at `for` (DDA) or `while` (Bresenham) statements
5. **Decision Logic** - Look for `if (d < 0)` or `if (e2 > -dy)`

---

## 🎯 Most Important Lines

### DDA (dda_single_line.c)
- **Line 19-20**: Core floating-point increments
- **Line 44-48**: Main drawing loop

### Bresenham Line (bresenham_line.c)
- **Line 17**: Initial error term
- **Line 52-64**: Decision and update logic

### Bresenham Circle (bresenham_circle.c)
- **Line 24**: Initial decision parameter
- **Line 10-17**: 8-way symmetry
- **Line 52-59**: Circle decision logic

---

## 📖 Cross-Reference

| Formula | DDA Location | Bresenham Line | Bresenham Circle |
|---------|--------------|----------------|------------------|
| dx calculation | Line 12 | Line 11 | N/A |
| dy calculation | Line 13 | Line 12 | N/A |
| Initial param | Lines 19-20 | Line 17 | Line 24 |
| Main loop | Lines 44-48 | Lines 42-65 | Lines 49-69 |
| Update formula | Lines 46-47 | Lines 56-63 | Lines 54, 58 |

---

**All formulas are now mapped to exact line numbers in your code files!** 🎯

Use this guide to quickly locate and understand where each mathematical formula is implemented.

