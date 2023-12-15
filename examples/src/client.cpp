#include <raylib.h>
#include <mapbuilder.hpp>

void draw_map_1(MapBuilder *mb) {
    mb->update_map_builder();
}

void draw_map_2(MapBuilder *mb) {
    mb->update_map_builder();
}

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
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; 
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
    //--------------------------------------------------------------------------------------

    while(!WindowShouldClose()) {
        // Ignore when running the Map Builder
        //----------------------------------------------------------------
        // UpdateCamera(&camera, CAMERA_FREE);        
        // mb_1.draw_all_models();
        //----------------------------------------------------------------
        // Switch between maps
        //----------------------------------------------------------------
        if(IsKeyPressed(KEY_KP_1)) {        // Press 1 for map_1
            map = "map_1";
        }
        if(IsKeyPressed(KEY_KP_2)) {        // Press 2 for map_2
            map = "map_2";
        }
        
        if(map == "map_1") {
            draw_map_1(&mb_1);
        }
        else {
            draw_map_2(&mb_2);
        }
        //----------------------------------------------------------------
    }  

    // Unload all textures and models
    mb_1.unload(); 
    mb_2.unload();

    CloseWindow();

    return 0;
}