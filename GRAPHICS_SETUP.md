# Graphics Programming Setup Guide

## 🎨 SDL2 Graphics Library Installation

SDL2 (Simple DirectMedia Layer) is a cross-platform library for graphics, audio, and input.

### Install SDL2 on Ubuntu/Linux:

```bash
sudo apt update
sudo apt install -y libsdl2-dev
```

**Enter your password when prompted.**

---

## 📁 Graphics Programs Available

### 1. **dda_line.c** - SDL2 Demo Version
Opens a graphical window and draws multiple colored lines automatically.

**Compile:**
```bash
gcc -o dda_line dda_line.c -lSDL2 -lm
```

**Run:**
```bash
./dda_line
```

**Features:**
- ✓ Opens 800x600 window
- ✓ Draws 7 different colored lines
- ✓ Shows DDA algorithm details in terminal
- ✓ Press ESC or close window to exit

---

### 2. **dda_interactive_graphics.c** - Interactive Click-to-Draw
Click in the window to draw your own lines!

**Compile:**
```bash
gcc -o dda_interactive_graphics dda_interactive_graphics.c -lSDL2 -lm
```

**Run:**
```bash
./dda_interactive_graphics
```

**How to Use:**
1. **First click** = Starting point (red dot appears)
2. **Second click** = Ending point (line is drawn in blue)
3. **Press 'C'** = Clear screen
4. **Press 'ESC'** = Exit

---

## 🚀 Quick Start (After Installing SDL2)

```bash
cd "/mnt/data/UR/graphic design"

# Compile the demo
gcc -o dda_line dda_line.c -lSDL2 -lm

# Run it
./dda_line
```

You should see a window pop up with colorful lines!

---

## 🔧 Troubleshooting

### Error: "SDL.h: No such file or directory"
**Solution:** SDL2 is not installed. Run:
```bash
sudo apt install libsdl2-dev
```

### Error: "cannot find -lSDL2"
**Solution:** Same as above, install SDL2 development package.

### Error: Window doesn't appear
**Solution:** 
- Make sure you're running in a graphical environment (not just terminal)
- Check if you have X11/Wayland display server running
- Try: `echo $DISPLAY` (should show something like `:0` or `:1`)

### Error: "Permission denied"
**Solution:**
```bash
chmod +x dda_line
./dda_line
```

---

## 📊 What SDL2 Does

SDL2 provides:
- **Window creation** - Opens graphical windows
- **Rendering** - Draws pixels, lines, shapes
- **Event handling** - Keyboard, mouse input
- **Hardware acceleration** - Uses GPU for fast graphics

---

## 🎯 DDA Algorithm in Graphics Context

The programs use the same DDA algorithm but render to a window:

```c
// Calculate increments
float xIncrement = dx / steps;
float yIncrement = dy / steps;

// Draw each pixel
for (int i = 0; i <= steps; i++) {
    SDL_RenderDrawPoint(renderer, round(x), round(y));
    x += xIncrement;
    y += yIncrement;
}
```

**Advantages over image files:**
- ✓ Immediate visual feedback
- ✓ Interactive (click to draw)
- ✓ Real-time rendering
- ✓ Can animate or modify dynamically

---

## 📚 Comparison: Old vs New Method

| Feature | PPM Image Files | SDL2 Graphics |
|---------|----------------|---------------|
| Installation | None needed | Need libsdl2-dev |
| Output | Static image file | Live window |
| Interaction | None | Mouse/keyboard |
| Viewing | Need image viewer | Immediate |
| Speed | Slow (file I/O) | Fast (GPU) |
| Best for | Batch processing | Interactive apps |

---

## 💡 Alternative: If SDL2 Installation Fails

If you can't install SDL2, you can still use:

1. **PPM image method** (original programs)
   - No installation needed
   - Generates image files
   - View with `eog` or convert to PNG

2. **ASCII art in terminal** (text-based)
   - No graphics library needed
   - Draws lines with characters
   - Works in any terminal

Would you like me to create the ASCII version too?

---

## 🎓 Learning Resources

- SDL2 Tutorial: https://lazyfoo.net/tutorials/SDL/
- SDL2 Documentation: https://wiki.libsdl.org/
- Computer Graphics: https://www.scratchapixel.com/

---

## ✨ Next Steps

1. ✓ Install SDL2: `sudo apt install libsdl2-dev`
2. ✓ Compile: `gcc -o dda_line dda_line.c -lSDL2 -lm`
3. ✓ Run: `./dda_line`
4. ✓ Try interactive version
5. ✓ Modify colors, add more lines
6. ✓ Experiment with different coordinates

---

**Enjoy your graphics programming! 🎨**

