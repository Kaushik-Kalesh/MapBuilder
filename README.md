# Map Builder for raylib games

This is a 3D Map Builder for games to be made using [raylib](https://www.raylib.com/) with C++

### About
- The Map Builder provides a *menu* for allowing real-time changes of the properties of a 3D model in the world, essentially *building a map*    
- The menu can be instatntiated by pressing the `MENU_KEY` which is `KEY_F1` by default, and `KEY_ENTER` saves the modified properties

![image](https://github.com/Kaushik-Kalesh/MapBuilder/assets/67593056/774b1b8e-36c2-44cc-914e-60976cc48741)  

- As shown in the image, the properties avaiable for changes are namely *position*, *rotation* and *scale* of a model
- The Map Builder also allows management of multiple maps

### Installation
Clone this repo, and then install the following dependencies:
- raylib [guide](https://github.com/raysan5/raylib/blob/master/README.md)
- nlohmann-json [guide](https://json.nlohmann.me/integration/package_managers/#cocoapods)
- pkg-config (for [examples](examples/)) [guide](https://www.google.com/search?q=pkg-config+install&oq=pkg-config+install&sourceid=chrome&ie=UTF-8)

### Example
A basic example is given below (can be found at [client.cpp](examples/src/client.cpp)), 
```cpp
#include <raylib.h>
#include <mapbuilder.hpp>

// Helper functions
//----------------------------------------------------------------
void draw_map_1(MapBuilder *mb) {
    mb->draw_map();
}

void draw_map_2(MapBuilder *mb) {
    mb->draw_map();
}

bool is_btn_in_focus(int pos_x, int pos_y, int width, int height) {
    int mouse_x = GetMouseX(), mouse_y = GetMouseY();
    return (mouse_x >= pos_x && mouse_x <= pos_x + width) && (mouse_y >= pos_y && mouse_y <= pos_y + height);;
}
//----------------------------------------------------------------

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
    MapBuilder mb_1("map_1");

    mb_1.add_model("turret", "models/obj/turret.obj");        // Add the model "turret" to the map_1
    mb_1.set_material_texture("turret", MATERIAL_MAP_DIFFUSE, "models/obj/turret_diffuse.png");

    mb_1.add_model("house", "models/obj/house.obj");        // Add the model "house" to the map_1
    mb_1.set_material_texture("house", MATERIAL_MAP_DIFFUSE, "models/obj/house_diffuse.png");
    
    // Initialize map_2
    MapBuilder mb_2("map_2");

    mb_2.add_model("house", "models/obj/house.obj");        // Add the model "house" to the map_2
    mb_2.set_material_texture("house", MATERIAL_MAP_DIFFUSE, "models/obj/house_diffuse.png");

    std::string map = "map_1";
    bool isMenuDisplayed = true;

    EnableCursor();
    //--------------------------------------------------------------------------------------

    while(!WindowShouldClose()) {
        // Ignore when running the Map Builder
        //----------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);        

        if(IsKeyPressed(KEY_F2)) {      // Reset the camera
            camera.position = (Vector3){ 50.0f, 50.0f, 50.0f }; 
            camera.target = (Vector3){0.0f, 0.0f, 0.0f};
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Menu to switch between maps
            //----------------------------------------------------------------
            if(isMenuDisplayed) {
                DrawRectangle(0, 0, screenWidth, screenHeight, Fade(SKYBLUE, 0.5f));

                DrawText("Choose Map", screenWidth / 2 - 60, screenHeight / 2 - 75, 20, RED);

                DrawRectangle(screenWidth / 2 - 50, screenHeight / 2 - 30, 100, 40, Fade(GREEN, 0.5f));
                DrawText("map_1", screenWidth / 2 - 30, screenHeight / 2 - 20, 20, RED);
                DrawRectangle(screenWidth / 2 - 50, screenHeight / 2 + 30, 100, 40, Fade(GREEN, 0.5f));
                DrawText("map_2", screenWidth / 2 - 30, screenHeight / 2 + 40, 20, RED);

                if(is_btn_in_focus(screenWidth / 2 - 50, screenHeight / 2 - 30, 100, 40) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    map = "map_1";
                    isMenuDisplayed = false;
                }
                if(is_btn_in_focus(screenWidth / 2 - 50, screenHeight / 2 + 30, 100, 40) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    map = "map_2";
                    isMenuDisplayed = false;
                }
            }
            //----------------------------------------------------------------

            if(!isMenuDisplayed) {
                BeginMode3D(camera);
        
                    if(map == "map_1") {
                        draw_map_1(&mb_1);
                    }
                    else {
                        draw_map_2(&mb_2);
                    }

                EndMode3D();

                if(IsKeyPressed(KEY_F1)) {
                    isMenuDisplayed = true;
                }
            }

        EndDrawing();
        //----------------------------------------------------------------
        // mb_1.update_map_builder();
    }  

    // Unload all textures and models
    mb_1.unload(); 
    mb_2.unload();

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
