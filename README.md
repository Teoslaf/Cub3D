Cub3D Project README

Introduction:
Welcome to the Cub3D project, a graphics project designed to introduce students to the basics of raycasting and the fundamental principles of computer graphics. This project is part of the curriculum at 42, an innovative coding school focused on peer-to-peer learning and project-based education.

Project Overview:
Cub3D is inspired by the classic game Wolfenstein 3D, a first-person shooter developed by id Software and released in 1992. In this project, you will create a simplified version of the game engine using the C programming language and the powerful graphics library called MiniLibX.

Features:
- Raycasting Engine: Implement a basic raycasting engine to render a 3D perspective of a maze-like environment.
- Map Parsing: Read and parse a map file that describes the layout of the game world, including walls, sprites, player starting position, etc.
- Player Movement: Implement basic player controls for movement and rotation within the game world.
- Texture Rendering: Load and render wall textures to create a more immersive environment.
- Sprite Rendering: Render sprites within the game world, such as enemies or items.
- Collision Detection: Implement collision detection to ensure the player cannot walk through walls or other solid objects.
- HUD (Heads-Up Display): Display relevant information to the player, such as minimap, health, etc.

Getting Started:
To compile and run the Cub3D project, follow these steps:
1. Clone the project repository from the 42 GitLab.
2. Navigate to the project directory.
3. Run the make command to compile the project.
4. Execute the generated executable with a valid map file as an argument.

Usage:
./cub3D path_to_map_file.cub

Map File Format:
The map file contains the layout of the game world and follows a specific format. Here is an example:
R 1920 1080  // Resolution
NO ./textures/north_texture.xpm  // North-facing wall texture
SO ./textures/south_texture.xpm  // South-facing wall texture
WE ./textures/west_texture.xpm    // West-facing wall texture
EA ./textures/east_texture.xpm    // East-facing wall texture
S ./textures/sprite_texture.xpm   // Sprite texture
F 220,100,0    // Floor color (RGB)
C 0,128,128    // Ceiling color (RGB)
1111111111111111111111111  // Map representation, where '1' represents a wall
1000000000110000000000001
1011000001110000002000001
1001000000000000000000001
1111111111111111111111111

Controls:
- W: Move forward
- A: Rotate left
- S: Move backward
- D: Rotate right
- ← and →: Strafe left and right
- ESC: Exit the game

Dependencies:
- C compiler (gcc or clang)
- MiniLibX library
