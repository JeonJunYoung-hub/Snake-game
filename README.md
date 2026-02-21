# Snake Game (C++ MFC)

Classic Snake game implemented as a Windows MFC application.

## Overview

- Built using C++ and Microsoft Foundation Classes (MFC)
- Real-time movement controlled via Windows Timer
- Bitmap-based food rendering
- RGB-based snake body rendering
- Play time tracking displayed on side panel

## Implementation Details

- Used `SetTimer()` for game loop timing and movement updates  
- Implemented snake body rendering using RGB color values drawn directly on the window surface  
- Used bitmap resources to render food items  
- Managed collision detection by comparing RGB values of snake, food, and background  
- Implemented score/time tracking with a secondary timer displayed on the right panel  
- Structured core logic into separate functions to handle rendering, movement, and collision detection  

## Development Notes

- First project using C++ and MFC framework  
- Spent time understanding event-driven structure and message handling in MFC  
- Learned function separation and modular design in a Windows application architecture  

---

## Screenshot

<!-- Add game screenshot below -->

![Snake Game Screenshot](images/screenshot.png)


