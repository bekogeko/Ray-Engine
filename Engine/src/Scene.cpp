//
// Created by Bekir Gulestan on 3/23/24.
//

#include "Scene.h"
#include "ECS/Components.h"
#include "ECS/Entity.h"
#include "Engine.h"

#include <iostream>
#include "raylib.h"

namespace RayEngine {


    Scene::Scene() {
        entityRegistry.on_construct<TransformComponent>().connect<&Scene::OnTransformConstruct>();
    }

    Scene::~Scene() {

        std::cout << "Scene destroyed..." << std::endl;

        // Destroy all entities
        entityRegistry.clear();

    }

    void Scene::UpdateScene() {

        // Update all entities
        for(auto& entity: m_Entities){
            entity->Update(GetFrameTime());
        }


    }


    void Scene::OnTransformConstruct(entt::registry &registry, entt::entity entity) {
        // Add the entity to the transform group
    }

    void Scene::DrawScene() {

        auto view= entityRegistry.view<TransformComponent,BoxRenderer>();
        for(auto entity: view){
            auto [transform,renderer] = view.get<TransformComponent,BoxRenderer>(entity);
            auto vertices = renderer.GetVertices();
            auto indices = renderer.GetIndices();
            auto normals = renderer.GetNormals();
            auto position = transform.position;
            auto rotation = transform.rotation;

            for(auto& index: indices){
                auto [v1,v2,v3] = index;
                auto p1 = Vector2Rotate(v1,rotation);
                auto p2 = Vector2Rotate(v2,rotation);
                auto p3 = Vector2Rotate(v3,rotation);

                p1 = Vector2Add(p1,position);
                p2 = Vector2Add(p2,position);
                p3 = Vector2Add(p3,position);

                DrawTriangle(p1,p2,p3,RED);
            }
        }



//        // Draw all UI elements
//        auto uiView = entityRegistry.view<UIElement>();

    }

    void Scene::StartScene() {
        // Start all entities

        // go over m_Entities
        // call Start on each entity
        for(auto& entity: m_Entities){
            entity->Start();
        }
    }

    EntityID Scene::CreateEntity() {
        EntityID id = entityRegistry.create();
        entityRegistry.emplace<TransformComponent>(id);
//        entityRegistry.emplace<TagComponent>(id, "Object");
        return id;
    }

    void Scene::RecordEntity(Entity *entity) {
        m_Entities.push_back(std::shared_ptr<Entity>(entity));
    }


}












