

A 2D [Game/Simulation/Application] built with **C++** and the **SFML (Simple and Fast Multimedia Library)**. 

This project explores the "low-level" side of game development, handling the game loop, event processing, and rendering logic manually rather than using a high-level engine like Unity or Unreal.

---

## 🛠 Features
* **Custom Game Loop:** Managed frame-rate independent updates.
* **Asset Management:** Efficient loading of textures, fonts, and sounds.
* **Physics/Logic:** [e.g., Impulse-based physics, Vector math, and Dot product calculations for collisions].
* **Cross-Platform:** Designed to be compiled on Windows, Linux, and macOS.

---

## 🏗 How it Works (The "Iceberg" Insight)
While the `main.cpp` may look simple, this project utilizes deep layers of abstraction:
1. **C++ Standard Library:** Handles memory and I/O logic.
2. **SFML Layer:** Interfaces with OpenGL for hardware-accelerated 2D graphics.
3. **OS Kernel:** The program communicates with the OS via **System Calls** to create a window, manage memory, and capture keyboard/mouse input.

---

## 🚀 Getting Started

### Prerequisites
You will need a C++ compiler (GCC/Clang or MSVC) and the SFML development files installed on your system.
* **Windows:** Install SFML via [vcpkg](https://github.com/microsoft/vcpkg) or download the binaries.
* **Ubuntu/Debian:** `sudo apt-get install libsfml-dev`
* **MacOS:** `brew install sfml`

```bash
# Clone the repo
git clone [https://github.com/your-username/your-repo-name.git](https://github.com/your-username/your-repo-name.git)
cd your-repo-name

# Create build files
mkdir build && cd build
cmake ..

# Build and Run
cmake --build .
./[YourExecutableName]

