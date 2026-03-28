# **VOID\_SCAN**

VOID\_SCAN is a software-based game engine written in C using SDL2. It is designed to implement the core architectural patterns of 1990s pseudo-3D and 3D shooters, prioritizing CPU-side rasterization and manual memory management.

## **Technical Foundation**

The engine is built from the ground up to handle the "id Tech" style of game logic:

* **Software Rasterizer**: A custom pixel-pushing pipeline that renders directly to an SDL\_Surface.  
* **Fixed-Point Math**: All trigonometric and transformation calculations use integer-based fixed-point arithmetic to avoid floating-point non-determinism.  
* **Binary Space Partitioning**: Levels are processed into BSP trees to allow for efficient front-to-back rendering and perfect collision detection.  
* **Lump-Based Data**: All assets are packed into a single binary file with a custom directory header, allowing for fast seeking and loading of textures and maps.

## **Design Goals**

* **No GPU Acceleration**: All visual processing is handled by the CPU to maintain the "retro" feel and technical challenge.  
* **Zero Bloat**: Minimal external dependencies beyond SDL2.  
* **Performance**: Designed to maintain high frame rates on modern hardware despite the lack of hardware acceleration.

## **Requirements**

* C99 compliant compiler (GCC / Clang)  
* SDL2 (Development headers and library)  
* Make

## **Building the Engine**

To compile VOID\_SCAN, run:

Bash  
make

## **Running**

Once compiled, you can launch the engine with a level file:

Bash  
./void\_scan levels/e1m1.map

## **License**

MIT License

