#!/bin/bash
echo "🔥 Building CYBERFRONT: Digital Siege..."

# Install dependencies (Ubuntu/Debian)
if command -v apt &> /dev/null; then
    echo "Installing dependencies..."
    sudo apt update
    sudo apt install -y build-essential cmake libsfml-dev
fi

# Build
mkdir -p build
cd build
cmake ..
make -j$(nproc)

echo "🎮 Starting CYBERFRONT: Digital Siege..."
./cyberfront