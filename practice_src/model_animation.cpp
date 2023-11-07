#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Model Animation");
    SetWindowState(FLAG_WINDOW_MAXIMIZED);

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    Model model = LoadModel("../raylib/examples/models/resources/models/iqm/guy.iqm");                    // Load the animated model mesh and basic data
    Texture2D texture = LoadTexture("../raylib/examples/models/resources/models/iqm/guy.png");         // Load model texture and set material
    SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture);     // Set model material map texture

    Vector3 position = { 0.0f, 0.0f, 0.0f };            // Set model position

    // Load animation data
    int animsCount = 0;
    ModelAnimation *anims = LoadModelAnimations("../raylib/examples/models/resources/models/iqm/guyanim.iqm", &animsCount);
    int animFrameCounter = 0;

    DisableCursor();                    // Catch cursor
    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        if (IsKeyDown('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };

        // Play animation when spacebar is held down
        if (IsKeyDown(KEY_SPACE))
        {
            animFrameCounter++;
            UpdateModelAnimation(model, anims[0], animFrameCounter);
            if (animFrameCounter >= anims[0].frameCount) animFrameCounter = 0;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawModelEx(model, position, (Vector3){ 1.0f, 0.0f, 0.0f }, -90.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, WHITE);

                for (int i = 0; i < model.boneCount; i++)
                {
                    DrawCube(anims[0].framePoses[animFrameCounter][i].translation, 0.2f, 0.2f, 0.2f, RED);
                }

                DrawGrid(10, 1.0f);         // Draw a grid

            EndMode3D();

            DrawText("PRESS SPACE to PLAY MODEL ANIMATION", 10, 10, 20, MAROON);
            DrawText("(c) Guy IQM 3D model by @culacant", screenWidth - 200, screenHeight - 20, 10, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);                     // Unload texture
    UnloadModelAnimations(anims, animsCount);   // Unload model animations data
    UnloadModel(model);                         // Unload model

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}