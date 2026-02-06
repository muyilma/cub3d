*This project has been created as part of the 42 curriculum by omgorege, musyilma.*

# cub3D
My first RayCaster with miniLibX

---

## Description

**cub3D** is a graphical programming project inspired by the iconic game **Wolfenstein 3D**, widely recognized as the first true First-Person Shooter (FPS).

The objective of this project is to create a **realistic 3D representation of a maze** using **ray-casting techniques**, rendered from a **first-person perspective**.  
The project is entirely written in **C** and uses the **miniLibX** graphical library.

This project focuses on:
- Ray-casting mathematics
- Basic 3D rendering concepts
- Texture mapping
- Event handling (keyboard and window events)
- Parsing and validating configuration files

---

## Instructions

### Compilation
To compile the project, run:
```bash
make
```

This will create the `cub3D` executable.

### Usage
Run the program with a `.cub` map file as an argument:
```bash
./cub3D maps/map.cub
```

### Controls
- **W, A, S, D**: Move through the maze (forward, left, backward, right)
- **Left Arrow / Right Arrow**: Rotate camera (look left/right)
- **ESC**: Exit the program
- **Red Cross (X)**: Close window and exit

### Map File Format
The `.cub` file must contain:

**Texture Paths:**
```
NO ./path_to_north_texture.xpm
SO ./path_to_south_texture.xpm
WE ./path_to_west_texture.xpm
EA ./path_to_east_texture.xpm
```

**Colors (RGB format, range 0-255):**
```
F 220,100,0    (Floor color)
C 225,30,0     (Ceiling color)
```

**Map:**
- `0`: Empty space
- `1`: Wall
- `N`, `S`, `E`, `W`: Player starting position and orientation
- Map must be surrounded by walls

**Example `.cub` file:**
```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
```

### Cleaning
```bash
make clean
make fclean
make re
make run
make leak
```



## Features

- Real-time 3D first-person view
- Ray-casting based rendering engine
- Wall textures depending on orientation (North, South, East, West)
- Configurable floor and ceiling colors
- Smooth window management
- Player movement and camera rotation
- Strict `.cub` file validation with proper error handling

---
## Resources

Raycasting algorithm and math:
https://www.youtube.com/watch?v=NbSee-XM7WA 
https://lodev.org/cgtutor/raycasting.html

## AI Usage

In this project, we worked as a team of two, with each member handling different sections: one of us developed the parser section, while the other developed the executor section.

**Parser Section:**
- AI assistance was used to understand how the general structure should be set up
- Guidance was requested from AI regarding which cases need to be parsed
- After the structure was determined, the code was written entirely without AI assistance

**Executor Section:**
- AI was used to understand what ray-casting is and how it works
- Information was obtained about which MLX functions to use and how they operate
- AI guidance was received on how functions should connect with each other
- Code was written based on the directions provided by AI

In all AI interactions, the suggestions provided were questioned until they were understood and their logic was comprehended. No code block was integrated into the project without being understood or tested.