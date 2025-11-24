#!/bin/bash

echo "╔═══════════════════════════════════════════════════════════╗"
echo "║  SDL2 Graphics Library Setup for DDA Line Drawing        ║"
echo "╚═══════════════════════════════════════════════════════════╝"
echo ""

# Check if SDL2 is installed
if ! dpkg -l | grep -q libsdl2-dev; then
    echo "📦 SDL2 not found. Installing..."
    echo ""
    sudo apt update
    sudo apt install -y libsdl2-dev
    
    if [ $? -eq 0 ]; then
        echo ""
        echo "✓ SDL2 installed successfully!"
    else
        echo ""
        echo "✗ SDL2 installation failed. Please run manually:"
        echo "  sudo apt install libsdl2-dev"
        exit 1
    fi
else
    echo "✓ SDL2 is already installed!"
fi

echo ""
echo "─────────────────────────────────────────────────────────────"
echo "Compiling programs..."
echo ""

cd "/mnt/data/UR/graphic design"

# Compile demo version
echo "1. Compiling dda_line.c (demo version)..."
gcc -o dda_line dda_line.c -lSDL2 -lm

if [ $? -eq 0 ]; then
    echo "   ✓ dda_line compiled successfully!"
else
    echo "   ✗ Compilation failed!"
    exit 1
fi

# Compile interactive version
echo "2. Compiling dda_interactive_graphics.c (interactive)..."
gcc -o dda_interactive_graphics dda_interactive_graphics.c -lSDL2 -lm

if [ $? -eq 0 ]; then
    echo "   ✓ dda_interactive_graphics compiled successfully!"
else
    echo "   ✗ Compilation failed!"
    exit 1
fi

echo ""
echo "╔═══════════════════════════════════════════════════════════╗"
echo "║  ✓ Setup Complete!                                        ║"
echo "╚═══════════════════════════════════════════════════════════╝"
echo ""
echo "📁 Available programs:"
echo "   ./dda_line                    - Demo with multiple lines"
echo "   ./dda_interactive_graphics    - Click to draw lines"
echo ""
echo "🚀 Running demo program now..."
echo ""

# Run the demo
./dda_line

