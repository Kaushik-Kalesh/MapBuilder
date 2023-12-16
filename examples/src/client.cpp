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