//
// Created by Bekir Gulestan on 3/16/24.
//

#pragma once


#include "entt/entt.hpp"

class Engine;

namespace RayEngine
{

    class GameObject
    {
    private:
        // Warning this is unsigned int 32
        entt::entity m_EntityId;
    public:
        GameObject();

        virtual void Init() {};
        virtual void Update() = 0;
        virtual void Draw() = 0;
        virtual void DrawUI() {};

        void DrawDebug();
    };
}