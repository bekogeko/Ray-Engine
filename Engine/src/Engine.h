//
// Created by Bekir Gulestan on 3/19/24.
//

#pragma once

#include "raylib.h"
#include "entt/entt.hpp"

namespace RayEngine
{
    class Engine{
    public:

        static void Init(int width, int height, const char *title="RayEngine",int fps=120);

        // static create entity
        static entt::entity CreateEntity()  {
            return GetInstance().m_Registry.create();
        }

        // get the instance of the engine
        static Engine& GetInstance(){
            static Engine instance;
            return instance;
        }

    private:
        // ECS system using entt
        entt::registry m_Registry = entt::registry();
    };
}