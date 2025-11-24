# Bresenham's Circle Drawing Algorithm

## 🎯 Overview

The **Bresenham's Circle Algorithm** (also known as **Midpoint Circle Algorithm**) is an efficient method for drawing circles using only integer arithmetic.

---

## 🚀 How to Run

```bash
cd "/mnt/data/UR/graphic design"
./bresenham_circle
```

**Input Example:**
```
Enter the center coordinates:
  xc (center x): 400
  yc (center y): 300

Enter the radius:
  radius: 150
```

**Output:** A red circle with a blue crosshair at center!

---

## 🎨 Algorithm Explanation

### Key Concept: 8-Way Symmetry

A circle has **8-fold symmetry**. If we calculate one point, we can determine 7 other points!

```
         |
    2    |    1
         |
   ------+------
         |
    3    |    4
         |

Plus 4 more octants when we swap x and y!
```

**This means:** Calculate 1/8 of the circle → Get all 8 octants for free!

---

## 📐 Algorithm Steps

### Step 1: Initialize
```
x = 0
y = radius
d = 3 - 2*radius  (decision parameter)
```

### Step 2: Loop (while x ≤ y)
```
Plot 8 symmetrical points at (xc±x, yc±y) and (xc±y, yc±x)

Increment x

If d < 0:
    d = d + 4*x + 6           (choose East point)
Else:
    y = y - 1
    d = d + 4*(x - y) + 10   (choose South-East point)
```

### Step 3: Continue
Repeat until x > y (we've completed one octant)

---

## 💡 Why It Works

### Decision Parameter (d)
The parameter `d` helps decide which pixel to choose next:
- If `d < 0`: The midpoint is inside the circle → choose E (East)
- If `d ≥ 0`: The midpoint is outside the circle → choose SE (South-East)

### Mathematics Behind It
Based on the circle equation: `x² + y² = r²`

The decision parameter tracks: `d = (x+1)² + (y-0.5)² - r²`

But we use integer approximation: `d = 3 - 2r` initially

---

## 🔬 Example Calculation

**Circle:** Center (400, 300), Radius = 10

```
Initial state:
  x = 0, y = 10
  d = 3 - 2*10 = -17

Step 0: (0, 10)
  Plot: (400±0, 300±10) and (400±10, 300±0)
  8 points: (400,310), (400,290), (410,300), (390,300), etc.

Step 1: x=1
  d = -17 (< 0, choose E)
  d = -17 + 4*1 + 6 = -7
  Plot: (1, 10) → generates 8 points

Step 2: x=2
  d = -7 (< 0, choose E)
  d = -7 + 4*2 + 6 = 7
  Plot: (2, 10) → generates 8 points

Step 3: x=3
  d = 7 (≥ 0, choose SE)
  y = 9
  d = 7 + 4*(3-9) + 10 = -7
  Plot: (3, 9) → generates 8 points

...continue until x > y
```

---

## 🎯 8-Way Symmetry Explained

For a point (x, y) relative to center, we plot:

| Octant | Point | Description |
|--------|-------|-------------|
| 1 | (xc+x, yc+y) | East-South |
| 2 | (xc-x, yc+y) | West-South |
| 3 | (xc+x, yc-y) | East-North |
| 4 | (xc-x, yc-y) | West-North |
| 5 | (xc+y, yc+x) | South-East (swapped) |
| 6 | (xc-y, yc+x) | South-West (swapped) |
| 7 | (xc+y, yc-x) | North-East (swapped) |
| 8 | (xc-y, yc-x) | North-West (swapped) |

**Efficiency:** Calculate 1 point → Get 8 points!

---

## 💻 Code Structure

### Main Function:
```c
void drawCircleBresenham(int xc, int yc, int radius) {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;
    
    while (x <= y) {
        plotCirclePoints(xc, yc, x, y);  // Plot 8 points
        
        x++;
        
        if (d < 0) {
            d = d + 4*x + 6;
        } else {
            y--;
            d = d + 4*(x - y) + 10;
        }
    }
}
```

### Symmetry Function:
```c
void plotCirclePoints(int xc, int yc, int x, int y) {
    setPixel(xc + x, yc + y);  // Octant 1
    setPixel(xc - x, yc + y);  // Octant 2
    setPixel(xc + x, yc - y);  // Octant 3
    setPixel(xc - x, yc - y);  // Octant 4
    setPixel(xc + y, yc + x);  // Octant 5
    setPixel(xc - y, yc + x);  // Octant 6
    setPixel(xc + y, yc - x);  // Octant 7
    setPixel(xc - y, yc - x);  // Octant 8
}
```

---

## 📊 Advantages

✓ **Integer arithmetic only** - No floating point, very fast!
✓ **8-way symmetry** - Calculate 1/8, get whole circle
✓ **Efficient** - Minimal calculations per pixel
✓ **Accurate** - Pixel-perfect circles
✓ **Hardware-friendly** - Can be implemented in circuits

---

## 🎓 Sample Test Cases

### Small Circle:
```
xc: 400, yc: 300, radius: 50
Result: Small circle in center of window
```

### Large Circle:
```
xc: 400, yc: 300, radius: 250
Result: Large circle (may touch edges)
```

### Off-Center Circle:
```
xc: 600, yc: 400, radius: 150
Result: Circle towards bottom-right
```

### Multiple Circles (modify code):
Run program multiple times, or modify to draw multiple circles:
```
xc: 200, yc: 200, r: 100  (top-left)
xc: 600, yc: 200, r: 100  (top-right)
xc: 400, yc: 400, r: 150  (bottom-center)
```

---

## 🔧 Algorithm Variations

### Standard Bresenham Circle:
- Decision parameter: `d = 3 - 2*r`
- Updates: `d + 4*x + 6` or `d + 4*(x-y) + 10`

### Midpoint Circle (equivalent):
- Decision parameter: `d = 1 - r`
- Updates: `d + 2*x + 1` or `d + 2*(x-y) + 1`

**Both produce identical results!**

---

## 📈 Comparison with Other Methods

### Naive Method (Using Circle Equation):
```c
for (angle = 0; angle < 360; angle++) {
    x = xc + r * cos(angle * PI/180);
    y = yc + r * sin(angle * PI/180);
    setPixel(x, y);
}
```
**Problems:**
- ✗ Uses floating point (sin, cos)
- ✗ Very slow
- ✗ Gaps or overlaps in pixels
- ✗ Need to choose angle increment

### Bresenham Method:
```c
// Integer arithmetic only
x = 0; y = r; d = 3 - 2*r;
while (x <= y) {
    plot8Points(x, y);
    // Integer updates only
}
```
**Benefits:**
- ✓ Only integers
- ✓ Fast
- ✓ No gaps
- ✓ Optimal pixel selection

**Winner: Bresenham** (10-50x faster!)

---

## 🎨 Visual Output

The program displays:
- 🔴 **Red circle** - Your circle outline
- 🔵 **Blue cross** - Center point marker
- ⚪ **White background** - Clear canvas

---

## 🧮 Complexity Analysis

**Time Complexity:** O(r)
- Only need to calculate r/√2 points (one octant)
- 8-way symmetry gives remaining points

**Space Complexity:** O(1)
- Only need a few integer variables
- No arrays or extra storage

**Operations per pixel:**
- 1-2 integer additions
- 1-2 integer comparisons
- No multiplication or division in loop!

---

## 🔍 Common Issues & Solutions

### Issue: Circle looks like octagon
**Cause:** Radius too small (< 10 pixels)
**Solution:** Use radius ≥ 20 for smooth appearance

### Issue: Gaps in circle
**Cause:** Not plotting all 8 octants
**Solution:** Ensure plotCirclePoints() plots all 8 points

### Issue: Circle cut off at edges
**Cause:** Center + radius exceeds window size
**Solution:** Ensure: `xc ± r` and `yc ± r` within bounds

---

## 📚 Further Learning

**Try these experiments:**

1. **Filled Circle:** Modify to draw horizontal lines from -x to +x at each y
2. **Thick Circle:** Draw multiple circles with radius r, r+1, r+2, etc.
3. **Concentric Circles:** Loop with increasing radii
4. **Ellipse:** Extend algorithm for different x and y radii
5. **Arc:** Draw only certain octants for partial circles

---

## 🎯 Next Steps

1. ✓ Run the program with different radii
2. ✓ Try circles at different positions
3. ✓ Observe the 8-way symmetry in terminal output
4. ✓ Compare small (r=20) vs large (r=200) circles
5. ✓ Read the calculation details in terminal

---

**Bresenham's circle algorithm is used in:**
- CAD software
- Graphics libraries (OpenGL, DirectX internals)
- Game engines
- Display hardware
- Image processing

**It's the industry standard for circle drawing!** 🎉

