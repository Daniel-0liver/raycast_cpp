# Raycast Program

This project is a raycasting program in C++ created using SFML. Initially, the project started with OpenGL, but due to a grafic bug on WSL2, it was switched to SFML.

## Description

The raycasting program is designed to render 2D maps using a raycasting technique, which simulates a 3D perspective by casting rays from the player's point of view and determining where they intersect with walls.

## Features

- Rendering of 2D maps with a 3D perspective
- Player movement and interaction
- Wall collision detection

## Requirements

- SFML (Simple and Fast Multimedia Library)
- MAKE (The command-line tool that reads the Makefile and executes the build instructions.)

## Installation

1. Clone the repository:
   ```sh
	git clone https://github.com/Daniel-0liver/raycast_cpp.git
   ```
2. Navigate to the project directory:
   ```sh
	cd raycast_cpp
   ```
3. Install the required dependencies:
	```sh
	sudo apt-get install libsfml-dev
	```
4. Build the project using Make:
	```sh
	make
	```
 
