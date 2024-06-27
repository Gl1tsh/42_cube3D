# CUBE3D

<p align="center">
  <img width="1021" alt="cube3D_menu" src="https://github.com/Gl1tsh/42_cube3D/assets/69108289/35c25578-a16b-4231-97a4-9cdddd001b8a">
</p>

The Cube3D project at 42 school is an introductory project that focuses on creating a simple 3D graphics engine using the Raycasting technique. The objective of the project is to render a 3D maze-like environment on the screen using only 2D graphics primitives.

This project introduces students to several key concepts in computer graphics and game development, including:

- *Raycasting*: Students implement the Raycasting algorithm to render the 3D environment from a 2D perspective, calculating the distance of walls and casting rays to create the illusion of depth.

- *Texture Mapping*: The project involves texture mapping, where textures are applied to walls to give them a realistic appearance and enhance the visual quality of the rendered scene.

- *User Input Handling*: Students must handle user input, such as keyboard events, to allow the player to navigate through the 3D environment, move forward, backward, and rotate the camera view.

- *Map Parsing*: The project requires parsing a map file to generate the 3D maze environment dynamically, including the layout of walls, corridors, and the player's starting position.

- *Graphics Rendering*: Graphics primitives such as lines and rectangles are used to draw the walls, floors, and ceilings of the 3D environment on the screen.

- *Game Loop*: Students implement a game loop to continuously update the game state, handle user input, and render the graphics to provide an interactive gameplay experience.

In summary, the Cube3D project provides students with hands-on experience in computer graphics and game development. It allows them to apply their knowledge of mathematics, algorithms, and C programming to create a simple yet visually impressive 3D graphics engine using the Raycasting technique.

<p align="center">
  <img width="1020" alt="cube3D_game" src="https://github.com/Gl1tsh/42_cube3D/assets/69108289/e3caed5f-6e70-4499-876c-cdb03d9aaeb8">
</p>


# How to launch the game :

Run the command: ```make```
- Once compiled, launch the game with a valid map: ```./cub3D maps/good/<map of your choice>```
- Exemple, you can copy past this : ```./cub3D maps/good/shoji.cub```

Mouvement
| Commands                  | Move                            |
|---------------------------|---------------------------------|
| `W`/`A`/`S`/`D`           | front/left/down/right           |
| `mouse rotate`            | turn left or right              |
