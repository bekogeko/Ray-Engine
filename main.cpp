#include "raylib.h"
#include "PhyEngine/PhyEngine.h"
#include "Game/Player.h"
#include "Game/Obstacle.h"

#include <iostream>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    Player player = Player(0, 0);
    std::vector<Obstacle> obstacles = {
            Obstacle({-100, 100}, {300, 20}),
    };


    Camera2D camera = { 0 };
    camera.target = (Vector2){  0, 0 };
    camera.offset = (Vector2){ screenWidth/2, screenHeight/2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;



    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(120);               // Set our game to run at 120 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Physics
        //----------------------------------------------------------------------------------
        // Update PhyObjects properties
        // Apply forces and impulses
        //
        PhyEngine::UpdatePhysics();


        // Update Game Entities (Player, Obstacles, etc.)
        //----------------------------------------------------------------------------------
        player.Update();
        for (auto &obstacle : obstacles) {
            obstacle.Update();
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        {
            // Draw Game Entities
            //----------------------------------------------------------------------------------
            BeginMode2D(camera);

            DrawCircle(0, 0, 5, BLACK);


            // Draw player
            player.Draw();

            // Draw obstacles
            for (auto &obstacle : obstacles) {
                obstacle.Draw();
            }


            EndMode2D();
        }


        // Draw UI
        //----------------------------------------------------------------------------------
        {
            player.DrawUI();
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}