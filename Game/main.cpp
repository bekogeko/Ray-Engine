#include "raylib.h"
//#include "PhyEngine/PhyEngine.h"
#include "Player.h"
#include "Obstacle.h"

#include "Entry.h"

#include <iostream>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    {
//        Debug::SetDebugFlag(Debug::DebugFlags::DRAW_BOUNDING_BOX);
//        Debug::SetDebugFlag(Debug::DebugFlags::DRAW_ROTATION);
//        Debug::SetDebugFlag(Debug::DebugFlags::DRAW_VERTICES);
//        Debug::SetDebugFlag(Debug::DebugFlags::DRAW_NORMALS);

//        WARNING: Not Implemented Yet
//        Debug::SetDebugFlag(Debug::DebugFlags::DRAW_TRIANGLES);
    }


//    Player player = Player(0, 0);
//    std::vector<Obstacle> obstacles = {
//            Obstacle({-100, 100}, {300, 20}),
//    };


    Camera2D camera = { 0 };
    camera.target = (Vector2){  0, 0 };
    camera.offset = (Vector2){ screenWidth/2, screenHeight/2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.42f;


    // - Initialize the engine
    // - Initialize the window
    // - Initialize the Camera
    // - Initialize the physics engine
    // - Initialize the game entities
    //
    RayEngine::Engine::Init(screenWidth, screenHeight);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Physics
        //----------------------------------------------------------------------------------
        // Update PhyObjects properties
        // Apply forces and impulses
        //
        //        PhyEngine::UpdatePhysics();

        // Engine Update
        //----------------------------------------------------------------------------------
        // description
        //  this is the order of the update loop in the engine
        //
        // - Update physics
        // - Update Entities (Player, Obstacles, etc.)
        //
        // - Draw Entities (Player, Obstacles, etc.)
        // - Draw Debug
        // - Draw UI




        // Update Game Entities (Player, Obstacles, etc.)
        //----------------------------------------------------------------------------------
//        player.Update();
//        for (auto &obstacle : obstacles) {
//            obstacle.Update();
//        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        {
            // Draw Game Entities
            //----------------------------------------------------------------------------------
            BeginMode2D(camera);

            // Draw player
//            player.Draw();
//
//            // Draw obstacles
//            for (auto &obstacle : obstacles) {
//                obstacle.Draw();
//            }
//
//            // Draw Debug
//            player.DrawDebug();
//            for (auto &obstacle : obstacles) {
//                obstacle.DrawDebug();
//            }



            EndMode2D();
        }


        // Draw UI
        //----------------------------------------------------------------------------------
//        {
//            player.DrawUI();
//            for (auto &obstacle : obstacles) {
//                obstacle.DrawUI();
//            }
//        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}