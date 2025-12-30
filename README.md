

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

**Linux (Ubuntu/Debian):**
```bash
sudo apt-get install libsfml-dev

What I Learned
System Architecture: Understanding the Client-Server model of X11/Wayland (Linux) vs Win32 API (Windows).

Memory Management: Handling resource lifecycles and avoiding leaks in C++.

Low-Level Graphics: How a simple "Draw" command interacts with GPU drivers via the OS Kernel.

Physics Math: Implementing dot products and impulse-velocity changes for realistic movement.
