//
// Created by Bekir Gulestan on 3/23/24.
//

#include "Scene.h"
#include "ECS/Components.h"
#include "ECS/Entity.h"
#include "Engine.h"

#include <iostream>
#include "raylib.h"
#include "ECS/PhysicsBody.h"

namespace RayEngine {


    Scene::Scene() {
    }

    Scene::~Scene() {
        std::cout << "Scene destroyed..." << std::endl;
        // Clear all entities in the scene
        // components are destroyed automatically
        m_Entities.clear();

        // Destroy all entities
        for(auto& entity: m_Entities){
            entity.reset();
        }
    }

    void Scene::RecordEntity(std::unique_ptr<Entity> entity) {
        m_Entities.push_back(std::move(entity));
    }



    // Run update on every entity
    void Scene::UpdateScene() {
        // Update all entities
        for(auto& entity: m_Entities){
            entity->Update(GetFrameTime());
        }

        // Update all systems
        // - Update physics

        // get items with PhysicsBody component and TransformComponent
        auto physicsView = entityRegistry.view<PhysicsBody,TransformComponent>();

        for(auto entity: physicsView){
            auto [physicsBody,transform] = physicsView.get<PhysicsBody,TransformComponent>(entity);
            // Update position
            transform.position = Vector2Add(transform.position, Vector2Scale(physicsBody.velocity, GetFrameTime()));

            // Update velocity
            physicsBody.velocity = Vector2Add(physicsBody.velocity, Vector2Scale(physicsBody.acceleration, GetFrameTime()));

            // Update rotation
            transform.rotation += physicsBody.rotationalVelocity*GetFrameTime();
        }



        // everything is done in the physics system
        // - Update transforms
        auto transformView = entityRegistry.view<TransformComponent>();
        for(auto entity: transformView){
            auto& transform = transformView.get<TransformComponent>(entity);
            transform.UpdateLast();
        }
    }



    void Scene::DrawScene() {

        // Draw all entities
        auto boxRenderers = entityRegistry.view<TransformComponent,BoxRenderer>();
        for(auto entity: boxRenderers){
            auto [transform,renderer] = boxRenderers.get<TransformComponent,BoxRenderer>(entity);
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

            // if debug flag is set for normals
            if(Debug::HasFlags(Debug::DRAW_NORMALS)){
                for(auto& normal: normals){

                    auto start=position;

                    Vector2 offset = {0,0};
                    // set offset to half of the size
                    offset = Vector2Multiply(normal, Vector2Divide(renderer.GetSize(),{2,2}));

                    // rotate offset
                    offset = Vector2Rotate(offset,rotation);
                    // add position
                    start = Vector2Add(start,offset);



                    // calculate start position
                    // multiply normal by polygon size
                    auto end = start;

                    end = Vector2Add(end, Vector2Rotate(Vector2Scale(normal,10),rotation));



                    DrawCircleV(start,2,GRAY);
                    DrawCircleV(end,2,LIME);

                    DrawLineEx(start,end,2,BLUE);

                }

            }
        }

        // Draw all UI elements
//        auto uiView = entityRegistry.view<UIElement>();


    }

    void Scene::StartScene() {
        // Start all entities

        // go over m_Entities
        // calls overridden Start method
        for(auto& entity: m_Entities){
            entity->Start();
        }
    }

    EntityID Scene::CreateEntity() {
        EntityID id = entityRegistry.create();
        entityRegistry.emplace<TransformComponent>(id);
//        entityRegistry.emplace<TagComponent>(id, "Object");
        m_EntityIds.push_back(id);
        return id;
    }


    void Scene::DrawUI() {

    }


}












