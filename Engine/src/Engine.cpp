//
// Created by Bekir Gulestan on 3/19/24.
//


#include "Engine.h"
#include "Scene.h"




namespace RayEngine
{

    void Engine::Init(int width, int height, const char *title, int fps)
    {
        // Initialize the window and set the target fps
        InitWindow(width, height, title);
        SetTargetFPS(fps);

        // Initialize the scene
        get().m_Scene = std::make_shared<Scene>();
    }


    //  - Itereate through all the game objects
    //  - - For each game object, iterate through all the components
    //  - - - For each component,
    //  - - - - Update physics
    //  - - - - Update logic
    //  - - - - Draw
    void Engine::Update()
    {
        // if it is the first frame, start the scene


        // Update the scene
        get().m_Scene->UpdateScene();
    }

    void Engine::Draw(Camera2D camera) {

        // Clear the screen
        BeginDrawing();
        ClearBackground(RAYWHITE);

        {
            BeginMode2D(camera);

            // Draw the scene
            get().m_Scene->DrawScene();

            EndMode2D();
        }

        EndDrawing();

    }

    void Engine::Close() {
        CloseWindow();
    }


    std::shared_ptr<Scene> Engine::GetScene() {
        return get().m_Scene;
    }

    void Engine::Start() {
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