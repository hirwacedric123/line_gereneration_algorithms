# C Programming Guide - DDA Line Drawing Algorithm

## How to Run C Programs on Linux

### Step 1: Write Your C Code
Create a file with `.c` extension (e.g., `program.c`)

### Step 2: Compile Your Code
```bash
gcc -o output_name source_file.c
```

For programs using math functions, include the math library:
```bash
gcc -o output_name source_file.c -lm
```

### Step 3: Run Your Program
```bash
./output_name
```

---

## DDA Line Drawing Algorithm Programs

This directory contains two implementations of the DDA (Digital Differential Analyzer) line drawing algorithm:

### 1. dda_line.c (Demo Version)
**Description:** Draws multiple lines in different colors to demonstrate the algorithm.

**How to compile:**
```bash
gcc -o dda_line dda_line.c -lm
```

**How to run:**
```bash
./dda_line
```

**Output:** Creates `dda_output.ppm` with several colored lines

---

### 2. dda_interactive.c (Interactive Version)
**Description:** Allows you to input your own line coordinates interactively.

**How to compile:**
```bash
gcc -o dda_interactive dda_interactive.c -lm
```

**How to run:**
```bash
./dda_interactive
```

**Usage Example:**
```
Enter starting point (x1 y1): 100 100
Enter ending point (x2 y2): 700 500
Do you want to draw another line? (y/n): y
Enter starting point (x1 y1): 400 50
Enter ending point (x2 y2): 400 550
Do you want to draw another line? (y/n): n
```

**Output:** Creates `my_lines.ppm` with your custom lines

---

## Viewing Output Images

### Method 1: Using Eye of GNOME (eog)
```bash
eog dda_output.ppm
```

### Method 2: Convert to PNG (requires ImageMagick)
```bash
convert dda_output.ppm dda_output.png
```

Then open with any image viewer:
```bash
xdg-open dda_output.png
```

---

## About DDA Algorithm

The **Digital Differential Analyzer (DDA)** algorithm is used for drawing lines in computer graphics.

### Algorithm Steps:
1. Calculate dx = x2 - x1 and dy = y2 - y1
2. Determine the number of steps = max(|dx|, |dy|)
3. Calculate increments: x_inc = dx/steps, y_inc = dy/steps
4. Starting from (x1, y1), add increments and round to get pixel positions
5. Plot each point until reaching (x2, y2)

### Key Features:
- **Simple** to implement
- Works for lines with **any slope**
- Uses **floating-point** arithmetic
- Suitable for **raster displays**

---

## Quick Reference - Common GCC Commands

| Command | Description |
|---------|-------------|
| `gcc file.c` | Compile to `a.out` |
| `gcc -o name file.c` | Compile with custom output name |
| `gcc file.c -lm` | Link with math library |
| `gcc -Wall file.c` | Show all warnings |
| `gcc -g file.c` | Include debug information |
| `gcc -O2 file.c` | Optimize for performance |

---

## Troubleshooting

### "Permission denied" when running
```bash
chmod +x dda_line
./dda_line
```

### "Command not found: gcc"
```bash
sudo apt update
sudo apt install build-essential
```

### "No such file or directory" errors
Make sure you're in the correct directory:
```bash
pwd  # Check current directory
ls   # List files in current directory
```

---

## Image Format Information

**PPM (Portable Pixel Map)** is a simple image format:
- No compression
- Easy to generate programmatically
- Human-readable header
- Supported by most Linux image viewers

---

## Next Steps

1. ✓ Run the demo version to see DDA in action
2. ✓ Try the interactive version with your own coordinates
3. Experiment with different line patterns
4. Modify the code to change colors or image dimensions
5. Try implementing other graphics algorithms (Bresenham's line algorithm, circle drawing, etc.)

---

**Happy Coding! 🚀**

# line_gereneration_algorithms
