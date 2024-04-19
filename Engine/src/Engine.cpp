//
// Created by Bekir Gulestan on 3/19/24.
//


#include "Engine.h"
#include "Scene.h"




namespace RayEngine
{
    Engine::Engine(): m_IsDrawing(false) {
        std::cout << "Engine created..." << std::endl;
        m_Scene = std::make_shared<Scene>();
    }

    void Engine::Init(int width, int height, const char *title, int fps)
    {
        // Initialize the window and set the target fps
        InitWindow(width, height, title);
        SetTargetFPS(fps);
    }


    //  - Itereate through all the game objects
    //  - - For each game object, iterate through all the components
    //  - - - For each component,
    //  - - - - Update physics
    //  - - - - Update logic
    //  - - - - Draw
    void Engine::Update()
    {


        // update physics
        // update logic
        // - Update all systems
        // - Update all entities

        // Update all systems
        // - Update physics
//        PhysicsEngine::UpdatePhysics();

        // Update all entities
        get().m_Scene->UpdateScene();
    }

    void Engine::Draw() {

        // get the camera from the scene
        Camera2D camera = *get().m_Scene->GetCameraRef();

        // - Draw World (Entities)
        // - Draw Debug
        // - Draw UI

//        get().m_Scene->SetCamera(&camera);


        // Clear the screen
        BeginDrawing();
        ClearBackground(RAYWHITE);
        {
            // Draw the world
            BeginMode2D(camera);

            get().m_IsDrawing = true;

            // Draw the scene
            get().m_Scene->DrawScene();

            EndMode2D();
            get().m_IsDrawing = false;
        }
        {

            get().m_IsDrawing = true;
            // Draw UI
            get().m_Scene->DrawUI();

            get().m_IsDrawing = false;
        }

        EndDrawing();

    }

    void Engine::Close() {
        CloseWindow();

        // Close the scene
        // This will call the destructor of the scene
        // which will call the destructor of all the entities


        std::cout << "Engine closed... (scene reset)" << std::endl;

    }


    std::shared_ptr<Scene> Engine::GetScene() {
        return get().m_Scene;
    }

    void Engine::Start() {
        // Start the scene
        get().m_Scene->StartScene();
    }

    bool Engine::ShouldCloseWindow() {

        static bool isRunning = false;

        // in the first call, isRunning is false
        // so we set it to true
        // and return false
        // if isRunning is true, we return windowShouldClose
        // so the window will close

        if (!isRunning) {
            isRunning = true;
            Start();
            return false;
        }
        return WindowShouldClose();
    }



}