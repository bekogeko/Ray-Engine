//
// Created by Bekir Gulestan on 3/19/24.
//

#pragma once

#include "Debug.h"
#include "Scene.h"
#include "raylib.h"

namespace RayEngine
{
    class Engine{
    public:

        /// <summary>
        /// Initialize the engine
        /// </summary>
        static void Init(int width, int height, const char *title="RayEngine",int fps=120);

        /// <summary>
        /// Update the engine and all the game objects
        /// </summary>
        static void Update();

        /// <summary>
        /// Draw all the game objects
        /// </summary>
        static void Draw(Camera2D camera);




        /// <summary>
        /// Close the engine
        /// </summary>
        static void Close();

        /// <summary>
        /// Get the current scene
        /// </summary>
        static std::shared_ptr<Scene> GetScene();

        static bool ShouldCloseWindow();

        /// <summary>
        /// get instance of the engine
        /// </summary>
        static Engine& get(){
            static Engine instance;
            return instance;
        }
    private:
        // current scene
        std::shared_ptr<Scene> m_Scene;

        static void Start();

        ~Engine(){
            std::cout << "Engine destroyed..." << std::endl;
            m_Scene.reset();
        }


    };
}