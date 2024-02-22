# Cub3D

Cub3D is project a graphics project designed to introduce students to the basics of raycasting and the fundamental principles of computer graphics. This project is part of the curriculum at 42, an innovative coding school focused on peer-to-peer learning and project-based education.



## Project Overview:
Cub3D is inspired by the classic game Wolfenstein 3D, a first-person shooter developed by id Software and released in 1992. In this project, you will create a simplified version of the game engine using the C programming language and the powerful graphics library called MiniLibX.
## Features:
Features:
- Raycasting Engine: Implement a basic raycasting engine to render a 3D perspective of a maze-like environment.
- Map Parsing: Read and parse a map file that describes the layout of the game world, including walls, sprites, player starting position, etc.
- Player Movement: Implement basic player controls for movement and rotation within the game world.
- Texture Rendering: Load and render wall textures to create a more immersive environment.
- Sprite Rendering: Render sprites within the game world, such as enemies or items.
- Collision Detection: Implement collision detection to ensure the player cannot walk through walls or other solid objects.

## Installation:
To compile and run the Cub3D project, follow these steps:
- Clone the project repository.
- Navigate to the project directory.
- Run the make command to compile the project.
- Execute the generated executable with a valid map file as an argument.

## Usage: 
```bash
./cub3D path_to_map_file.cub
```
## Map File Format:
The map file contains the layout of the game world and follows a specific format. Here is an example:
R 1920 1080  // Resolution
NO ./textures/north_texture.xpm  // North-facing wall texture
SO ./textures/south_texture.xpm  // South-facing wall texture
WE ./textures/west_texture.xpm    // West-facing wall texture
EA ./textures/east_texture.xpm    // East-facing wall texture

F 220,100,0    // Floor color (RGB)
C 0,128,128    // Ceiling color (RGB)

Map representation, where 'N', 'S', 'W' or 'E' represents the player.\
Map representation, where '0' empty space.\
Map representation, where '1' represents a wall.

## Controls:
- W: Move forward
- A: Rotate left 
- S: Move backward 
- D: Rotate right 
- M: toggle minimap
- ← and →: Strafe left and right 
- ESC: Exit the game
- 
## Dependencies:
 - C compiler (gcc or clang)
 - MiniLibX library
