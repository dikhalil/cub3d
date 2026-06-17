# cub3D

A raycasting game engine inspired by Wolfenstein 3D, built with **C** and **miniLibX**.
Project from the [42](https://42.fr) common core curriculum.

## Overview

cub3D parses a `.cub` configuration map file and renders a real-time 3D first-person view using **DDA (Digital Differential Analyzer)** raycasting. The player can navigate a maze-like environment with textured walls, colored floor/ceiling, and mouse-look controls.

## Features
- Raycasting engine with DDA algorithm
- Textured walls (4-directional: north, south, east, west)
- Customizable floor and ceiling colors (RGB)
- Player movement: forward/backward, strafing, rotation
- Mouse look
- Collision detection against walls
- Map validation: enclosed walls, valid player position
- Configurable via `.cub` map files

## Requirements

- **OS**: Linux
- **Compiler**: `cc` (gcc/clang)
- **Libraries**:
  - [miniLibX](https://github.com/42Paris/minilibx-linux) (`libmlx`, `libXext`, `libX11`)
  - `libbsd`
  - `libm` (math)

## Installation

### 1. Install miniLibX

```bash
# Debian / Ubuntu
sudo apt install libx11-dev libxext-dev libbsd-dev

# Clone and build miniLibX
git clone https://github.com/42Paris/minilibx-linux.git
cd minilibx-linux
make
sudo cp mlx.h /usr/local/include/
sudo cp libmlx.a /usr/local/lib/
```

### 2. Build cub3D

```bash
make
```

This compiles `libft` and the cub3D binary.

### 3. Run

```bash
./cub3D maps/map.cub
```

## Controls

| Key          | Action           |
|--------------|------------------|
| `W` / `↑`    | Move forward     |
| `S` / `↓`    | Move backward    |
| `A`          | Strafe left      |
| `D`          | Strafe right     |
| `←`          | Rotate left      |
| `→`          | Rotate right     |
| Mouse        | Look around      |
| `ESC` / `Q`  | Quit             |

## Map File Format

A `.cub` file defines the scene:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

C 135,206,235
F 100,100,100

         1111111111111111111111111
         1000000000110000000000001
         ...
11110111 1110101 1011110100011111
11111111 1111111 111111111111
```

- **Texture lines**: `NO`, `SO`, `WE`, `EA` followed by a path to an XPM file
- **Color lines**: `C` (ceiling) and `F` (floor) followed by `R,G,B`
- **Map**: `1` = wall, `0` = open space, `N/S/E/W` = player start position and facing direction
- Spaces represent voids (must be surrounded by walls)

## Project Structure

```
cub3d/
├── include/          # Header files
│   └── cub3d.h
├── libft/            # Custom C library (ft_printf, GNL, etc.)
├── maps/             # .cub map files
│   └── map.cub
├── src/
│   ├── cleanup/      # Memory deallocation, exit handler
│   ├── parser/       # Map file parsing
│   ├── render/       # Raycasting, drawing, movement, hooks
│   ├── utils/        # Utility functions
│   └── validator/    # Map validation (textures, colors, map closure)
├── textures/         # XPM wall textures
└── Makefile
```

## Makefile Targets

| Target   | Description                    |
|----------|--------------------------------|
| `all`    | Build the binary               |
| `clean`  | Remove object files            |
| `fclean` | Remove objects + binary        |
| `re`     | Clean and rebuild              |

## Authors

- **dikhalil** — [dikhalil@student.42amman.com](mailto:dikhalil@student.42amman.com)
- **amashhad** — [amashhad@student.42amman.com](mailto:amashhad@student.42amman.com)
