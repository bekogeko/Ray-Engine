//
// Created by Bekir Gulestan on 3/23/24.
//

#pragma once

#include <entt/entt.hpp>
#include <memory>
#include "raylib.h"

// defined EntityID to be an entt::entity
#define EntityID entt::entity


namespace RayEngine {
    class Entity;

    class Scene {
    public:
        Scene(Camera2D* camera);
        ~Scene();

        EntityID CreateEntity();
        void RecordEntity(std::unique_ptr<Entity> entity);

        void StartScene();
        void UpdateScene();
        void DrawScene();
        void DrawUI();

        // all_of
        template<typename T>
        bool HasComponent(EntityID entity) {
            return entityRegistry.all_of<T>(entity);
        }

        // emplace
        template<typename T, typename... Args>
        T& AddComponent(EntityID entity, Args&&... args) {
            if(HasComponent<T>(entity)) {
                return GetComponent<T>(entity);
            }
            return entityRegistry.emplace<T>(entity, std::forward<Args>(args)...);
        }

        // get
        template<typename T>
        T& GetComponent(EntityID entity) {
            if(HasComponent<T>(entity)) {
                return entityRegistry.get<T>(entity);
            }else {
                throw std::runtime_error("Entity does not have component");
            }
        }

        Camera2D GetCamera() { return *m_Camera; }
//        void SetCamera(Camera2D* camera) {
////            m_Camera = std::shared_ptr<Camera2D>(camera);
////            m_Camera.reset(camera);
//        }

    private:
        entt::registry entityRegistry;
        std::vector<EntityID> m_EntityIds;

//        std::vector<std::shared_ptr<Entity>> m_Entities;
        std::vector<std::unique_ptr<Entity>> m_Entities;

        std::shared_ptr<Camera2D> m_Camera;
    };


}
