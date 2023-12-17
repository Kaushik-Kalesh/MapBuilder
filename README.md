# Map Builder for raylib games

This is a 3D Map Builder for games to be made using [raylib](https://www.raylib.com/) with C++

### About
<<<<<<< HEAD

- The Map Builder provides an interface to place **static** models in the world in their desired places (*map designing*), without having to **recompile** every time a change is made
- In other words, the Map Builder provides a *menu* for allowing real-time changes of the properties of a 3D model in the world, essentially *building a map*
=======
- The Map Builder provides a *menu* for allowing real-time changes of the *properties* (transform) of a 3D model in the world, essentially *building a map*    
>>>>>>> a5b3ed62e46806490e97dc4866ddc7414afdb408
- The menu can be instatntiated by pressing the `MENU_KEY` which is `KEY_F1` by default, and `KEY_ENTER` saves the modified properties

![image](https://github.com/Kaushik-Kalesh/MapBuilder/assets/67593056/774b1b8e-36c2-44cc-914e-60976cc48741)  

- As shown in the image, the properties avaiable for changes are namely `position`, `rotation` and `scale` of a model
- The Map Builder also allows management of multiple maps

### Installation

Clone this repo, and then install the following dependencies:

- raylib [guide](https://github.com/raysan5/raylib/blob/master/README.md)
- nlohmann-json [guide](https://json.nlohmann.me/integration/package_managers/#cocoapods)
- pkg-config (for [examples](examples/)) [guide](https://www.google.com/search?q=pkg-config+install&oq=pkg-config+install&sourceid=chrome&ie=UTF-8)

### Example
<<<<<<< HEAD

A sample usage is shown below,

=======
A basic example is given below (can be found at [client.cpp](examples/src/client.cpp)), 
>>>>>>> a5b3ed62e46806490e97dc4866ddc7414afdb408
```cpp
#include <raylib.h>
#include <mapbuilder.hpp>

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "GAME");
    SetWindowState(FLAG_WINDOW_MAXIMIZED);                               
    SetTargetFPS(60);

    // Define the camera (3D)
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 50.0f, 50.0f, 50.0f }; 
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};                      
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };       
    camera.fovy = 45.0f;                                
    camera.projection = CAMERA_PERSPECTIVE; 
    
    // Initialize map_1
    MapBuilder mb("map_1");

    mb.add_model("turret", "models/obj/turret.obj");        // Add the model "turret" to the map_1
    mb.set_material_texture("turret", MATERIAL_MAP_DIFFUSE, "models/obj/turret_diffuse.png");

    mb.add_model("house", "models/obj/house.obj");        // Add the model "house" to the map_1
    mb.set_material_texture("house", MATERIAL_MAP_DIFFUSE, "models/obj/house_diffuse.png");
    
    //--------------------------------------------------------------------------------------

    while(!WindowShouldClose()) {
        // Ignore when running the Map Builder
        //----------------------------------------------------------------
        // UpdateCamera(&camera, CAMERA_FIRST_PERSON);        

        // if(IsKeyPressed(KEY_F2)) {      // Reset the camera
        //     camera.position = (Vector3){ 50.0f, 50.0f, 50.0f }; 
        //     camera.target = (Vector3){0.0f, 0.0f, 0.0f};
        // }

        // BeginDrawing();

        //     ClearBackground(RAYWHITE);
            
        //     BeginMode3D(camera);

        //         mb.draw_map();

        //     EndMode3D();
            
        // EndDrawing();
        //----------------------------------------------------------------

        mb.update_map_builder();
    }  

    mb.unload();        // Unload all textures and models

    CloseWindow();

    return 0;
}
```

Run the following in GNU/Linux or MacOS to build and run the example:

```bash
cd examples
make
```

In Windows use the `mingw32-make` tool  

Check [examples](examples/) for more info

### Credits

Created by shab & Kaushik Kalesh

`Copyright (C) 2023 MTCP-Labs. All Rights Reserved.`
