
#include "RayEngine.h"
#include "Player.h"
#include "Obstacle.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    int help = 2;
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

    {
        auto currentScene = RayEngine::Engine::GetScene();
        auto camera = RayEngine::Engine::GetScene()->GetCameraRef();
        camera->target = (Vector2){  0, 0 };
        camera->offset = (Vector2){ screenWidth/2, screenHeight/2 };
        camera->rotation = 0.0f;
        camera->zoom = 1.42f;
    }

    // - Initialize the engine
    RayEngine::Engine::Init(screenWidth, screenHeight);

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
        RayEngine::Engine::Draw();

    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RayEngine::Engine::Close();       // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}