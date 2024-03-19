//
// Created by Bekir Gulestan on 3/19/24.
//


#include "Engine.h"


namespace RayEngine
{
    void Engine::Init(int width, int height, const char *title, int fps)
    {
        // Initialize the window and set the target fps
        InitWindow(width, height, title);
        SetTargetFPS(fps);
        // Init the ECS system
        GetInstance().m_Registry = entt::registry();




    }
}