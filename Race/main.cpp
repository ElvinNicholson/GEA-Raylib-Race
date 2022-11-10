/*******************************************************************************************
*
*   raylib-cpp [core] example - Basic window (adapted for HTML5 platform)
*
*   This example is prepared to compile for PLATFORM_WEB, PLATFORM_DESKTOP and PLATFORM_RPI
*   As you will notice, code structure is slightly diferent to the other examples...
*   To compile it for PLATFORM_WEB just uncomment #define PLATFORM_WEB at beginning
*
*   This example has been created using raylib-cpp (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib-cpp.hpp"
#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 1920;
int screenHeight = 1080;

raylib::Camera3D camera;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame

//----------------------------------------------------------------------------------
// Main Enry Point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    raylib::Window window(screenWidth, screenHeight, "raylib-cpp [core] example - basic window");
    // Define the camera to look into our 3d world

    camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    SetCameraMode(camera, CAMERA_FREE);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!window.ShouldClose())    // Detect window close button or ESC key
    {
        UpdateCamera(&camera);
        if (IsKeyDown('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        UpdateDrawFrame();
    }
#endif

    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        DrawCube(Vector3{0, 0, 0}, 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires(Vector3{0, 0, 0}, 2.0f, 2.0f, 2.0f, GREEN);

        DrawCube(Vector3{0, 4, 0}, 2.0f, 4.0f, 2.0f, BLUE);
        DrawCubeWires(Vector3{0, 4, 0}, 2.0f, 4.0f, 2.0f, BLACK);

        DrawGrid(10, 1.0f);
        EndMode3D();

    DrawRectangle( 10, 10, 640, 266, Fade(SKYBLUE, 0.5f));
    DrawRectangleLines( 10, 10, 640, 266, BLUE);

    DrawText("Free camera default controls:", 20, 20, 20, BLACK);
    DrawText("- Mouse Wheel to Zoom in-out", 40, 60, 20, DARKGRAY);
    DrawText("- Mouse Wheel Pressed to Pan", 40, 80, 20, DARKGRAY);
    DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 100, 20, DARKGRAY);
    DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 120, 20, DARKGRAY);
    DrawText("- Z to zoom to (0, 0, 0)", 40, 140, 20, DARKGRAY);
    EndDrawing();
    //----------------------------------------------------------------------------------
}
