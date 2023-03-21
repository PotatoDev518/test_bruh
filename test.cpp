#include "raylib.h"

int main(void){

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - loading gltf");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = Vector3{ 5.0f, 5.0f, 5.0f };    // Camera position
    camera.target = Vector3{ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    // Load gltf model
    Model model = LoadModel("src/bruh3_.glb");

    // Load gltf model animations
    unsigned int animsCount = 0;
    unsigned int animIndex = 0;
    unsigned int animCurrentFrame = 0;
    ModelAnimation* modelAnimations = LoadModelAnimations("src/bruh3_.glb", &animsCount);

    Vector3 position = { 0.0f, 0.0f, 0.0f }; 

    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);
        // Select current animation
        if (IsKeyPressed(KEY_UP)) animIndex = (animIndex + 1) % animsCount;
        else if (IsKeyPressed(KEY_DOWN)) animIndex = (animIndex + animsCount - 1) % animsCount;

        // Update model animation
        ModelAnimation anim = modelAnimations[animIndex];
        animCurrentFrame = (animCurrentFrame + 1) % anim.frameCount;
        //UpdateModelAnimation(model, anim, animCurrentFrame);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawModel(model, position, 1.0f, WHITE);
        DrawGrid(10, 1.0f);

        EndMode3D();

        DrawText("Use the UP/DOWN arrow keys to switch animation", 10, 10, 20, GRAY);

        EndDrawing();
    }

    UnloadModel(model);         // Unload model and meshes/material

    CloseWindow();
}
