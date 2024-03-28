//
// Created by Bekir Gulestan on 3/23/24.
//

#pragma once

#include "entt/entt.hpp"
#include "Scene.h"
#include "Components.h"
#include <iostream>

namespace RayEngine {

    class Entity {
    public:
        Entity();
        Entity(EntityID id,  std::shared_ptr<Scene> scene);
        Entity(const Entity& other) = default;

        virtual ~Entity(){
            std::cout << "Entity destroyed..." << std::endl;
            m_Scene.reset();
        }


        template<typename T>
        bool HasComponent() {
            return m_Scene->HasComponent<T>(m_Id);
        }

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args) {
            return m_Scene->AddComponent<T>(m_Id, std::forward<Args>(args)...);
        }

        template<typename T>
        T& GetComponent() {
            return m_Scene->GetComponent<T>(m_Id);
        }


        virtual void Start(){};
        virtual void Update(float deltaTime){};




    private:
        EntityID m_Id{ entt::null};
        std::shared_ptr<Scene> m_Scene = nullptr;
    };

}