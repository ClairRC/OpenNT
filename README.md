
# ✨OpenNT✨ (thank you gamut)


This is a game engine project that I am doing in order to really figure out how that stuff works under the hood.

It is currently very much a work in progress.

### Current Features

* Simple abstractions for rendering, lighting, input handling, and resource management

* Simple ECS architecture in place the FOUNDATION is there

* Custom math libraries. For fun!

### TODO

* Refactor the systems that currently exist for better organization

* Allow 3D models

* Better handling of resources

* Custom scripting

* The list goes on... and on... Like I said it's just a start!

### How to Use
A CMake file is included, so you just have to run CMake and it will build the project for you. From there, main.cpp exists just as a demo, but anything put in main() and gameLoop() will be processed still.

Currently, this isn't good for too much more than messing around. But hey, I think it's kinda cool still :)

### Dependencies

* GLAD
* stb_images
* GLFW

The first two are already included as they are header only, and GLFW gets downloaded with CMake, so it shouldn't be difficult to set up.

