
#include "RayEngine.h"
#include "Player.h"
#include "Obstacle.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    {
        Debug::SetDebugFlag(Debug::DebugFlags::DRAW_BOUNDING_BOX);
        Debug::SetDebugFlag(Debug::DebugFlags::DRAW_ROTATION);
        Debug::SetDebugFlag(Debug::DebugFlags::DRAW_VERTICES);
        Debug::SetDebugFlag(Debug::DebugFlags::DRAW_NORMALS);
        Debug::SetDebugFlag(Debug::DebugFlags::DRAW_TRIANGLES);
        Debug::SetDebugFlag(Debug::DebugFlags::DRAW_COLLISION);
    }

    Camera2D camera = { 0 };
    camera.target = (Vector2){  0, 0 };
    camera.offset = (Vector2){ screenWidth/2, screenHeight/2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.42f;



    // - Initialize the engine
    RayEngine::Engine::Init(camera,screenWidth, screenHeight);

    Player player;
    Obstacle obstacle1({100, 100}, {50, 50});

    Obstacle obstacle2({0, 100}, {50, 50});

    // Main game loop
    while (!RayEngine::Engine::ShouldCloseWindow())    // Detect window close button or ESC key
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
        RayEngine::Engine::Update();

        // - Draw Entities (Player, Obstacles, etc.)
        // - Draw Debug
        // - Draw UI
        RayEngine::Engine::Draw(camera);


        // Update Game Entities (Player, Obstacles, etc.)
        //----------------------------------------------------------------------------------
//        player.Update();
//        for (auto &obstacle : obstacles) {
//            obstacle.Update();
//        }

        // Draw
        //----------------------------------------------------------------------------------
//        BeginDrawing();
//        ClearBackground(RAYWHITE);
//        {
//            // Draw Game Entities
//            //----------------------------------------------------------------------------------
//            BeginMode2D(camera);
//
//            // Draw player
////            player.Draw();
////
////            // Draw obstacles
////            for (auto &obstacle : obstacles) {
////                obstacle.Draw();
////            }
////
////            // Draw Debug
////            player.DrawDebug();
////            for (auto &obstacle : obstacles) {
////                obstacle.DrawDebug();
////            }
//
//
//
//            EndMode2D();
//        }


        // Draw UI
        //----------------------------------------------------------------------------------
//        {
//            player.DrawUI();
//            for (auto &obstacle : obstacles) {
//                obstacle.DrawUI();
//            }
//        }
//        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RayEngine::Engine::Close();       // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}