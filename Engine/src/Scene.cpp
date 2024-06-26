//
// Created by Bekir Gulestan on 3/23/24.
//

#include "Scene.h"
#include "RayEngine.h"

#include <iostream>
namespace RayEngine {


    Scene::Scene(): m_Camera(std::make_shared<Camera2D>()) {
        std::cout << "Scene created..." << std::endl;

    }

    Scene::~Scene() {
        std::cout << "Scene destroyed..." << std::endl;
    }

    void Scene::RecordEntity(Entity* entity) {
        m_Entities.push_back(entity);
    }



    // Run update on every entity
    void Scene::UpdateScene() {
        using namespace RayEngine;

        // Update all entities
        for(auto& entity: m_Entities){
            entity->Update(GetFrameTime());
        }

        // Update all systems
        // - Update physics

        // get items with PhysicsBody component and TransformComponent
        auto physicsView = entityRegistry.view<PhysicsBody,Transform>();

        // Update positions and velocities
        for(auto entity: physicsView){
            auto [physicsBody,transform] = physicsView.get<PhysicsBody,Transform>(entity);
            // Update position
            transform.position = Vector2Add(transform.position, Vector2Scale(physicsBody.velocity, GetFrameTime()));

            // Update velocity
            physicsBody.velocity = Vector2Add(physicsBody.velocity, Vector2Scale(physicsBody.acceleration, GetFrameTime()));

            // Update rotation
            transform.rotation += (physicsBody.rotationalVelocity * GetFrameTime() ) * RAD2DEG;
        }

        // collision detection
        auto colliderView = entityRegistry.view<BoxRenderer,PhysicsBody,Transform>();

        for (auto colliderBody: colliderView) {
            auto [collider,physicsBody,transform] = colliderView.get<BoxRenderer,PhysicsBody,Transform>(colliderBody);
            auto colliderBounds = collider.GetBoundingBox(transform.position,transform.rotation);

            for (auto otherBody: colliderView) {
                if (colliderBody == otherBody) continue;

                auto otherCollider = colliderView.get<BoxRenderer>(otherBody);
                auto otherPhysicsBody = colliderView.get<PhysicsBody>(otherBody);
                auto otherTransform = colliderView.get<Transform>(otherBody);


                auto otherBounds = otherCollider.GetBoundingBox(otherTransform.position, otherTransform.rotation);

                if (CheckCollisionRecs(colliderBounds, otherBounds)) {
                    // collision detected
                    // we can add a collision component to the entities
                    // and then we can check for collision components
                    // and then we can call OnCollision on the entities


                    // if Debug::DRAW_COLLISION is set
                    if(Debug::HasFlags(Debug::DRAW_COLLISION)){
                        // convert Collider bounds to world space
                        // fix width and height
                        auto worldPos = GetWorldToScreen2D({colliderBounds.x,colliderBounds.y},*m_Camera);
                        auto worldSize = Vector2Scale({colliderBounds.width,colliderBounds.height},m_Camera->zoom);
                        DrawRectangleLinesEx({worldPos.x,worldPos.y,worldSize.x,worldSize.y},5,RED);
                    }
                }
            }
        }



        // everything is done in the physics system
        // - Update transforms
        auto transformView = entityRegistry.view<Transform>();
        for(auto entity: transformView){
            auto& transform = transformView.get<Transform>(entity);
            transform.UpdateLast();
        }
    }



    void Scene::DrawScene() {

        // Draw all entities
        auto boxRenderers = entityRegistry.view<Transform,BoxRenderer>();
        for(auto entity: boxRenderers){
            auto [transform,renderer] = boxRenderers.get<Transform,BoxRenderer>(entity);

            auto indices = renderer.GetIndices();
            auto position = transform.position;
            auto rotation = transform.rotation;

            for(auto& index: indices){
                auto [v1,v2,v3] = index;
                auto p1 = Vector2Rotate(v1,rotation.GetRadians());
                auto p2 = Vector2Rotate(v2,rotation.GetRadians());
                auto p3 = Vector2Rotate(v3,rotation.GetRadians());

                p1 = Vector2Add(p1,position);
                p2 = Vector2Add(p2,position);
                p3 = Vector2Add(p3,position);

                // draw triangle
                DrawTriangle(p1,p2,p3,renderer.GetColor());
                // we might want to draw the lines with
                // DrawTriangleStrip
                // How it works:
                // You pass an array of points and it draws the triangles
                // in order of the points in the array
                // DrawTriangleStrip(Vector2* points, int pointsCount, Color color);

                if(Debug::HasFlags(Debug::DRAW_TRIANGLES)){
                    DrawLineEx(p1,p2,1,BLUE);
                    DrawLineEx(p2,p3,1,BLUE);
                    DrawLineEx(p3,p1,1,BLUE);
                }
            }

            // if debug flag is set for normals
            if(Debug::HasFlags(Debug::DRAW_NORMALS)){
                auto normals = renderer.GetNormals();
                for(auto& normal: normals){

                    auto start=position;

                    Vector2 offset = {0,0};
                    // set offset to half of the size
                    offset = Vector2Multiply(normal, Vector2Divide(renderer.GetSize(),{2,2}));

                    // rotate offset
                    offset = Vector2Rotate(offset,rotation.GetRadians());
                    // add position
                    start = Vector2Add(start,offset);


                    // calculate start position
                    // multiply normal by polygon size
                    auto end = start;

                    end = Vector2Add(end, Vector2Rotate(Vector2Scale(normal,10),rotation.GetRadians()));

                    DrawCircleV(start,2,GRAY);
                    DrawCircleV(end,2,LIME);

                    DrawLineEx(start,end,2,BLUE);

                }
            }

            if (Debug::HasFlags(Debug::DRAW_VERTICES)){
                auto vertices = renderer.GetVertices();
                for(auto& vertex: vertices) {
                    auto p = Vector2Rotate(vertex, rotation.GetRadians());
                    p = Vector2Add(p, position);
                    DrawCircleV(p, 2, BLUE);
                }
            }

            if(Debug::HasFlags(Debug::DRAW_ROTATION)){
                DrawCircleSector(position,10,0 ,rotation,8,BLUE);
                DrawText(TextFormat("Rotation %.f",(float)rotation),position.x+50,position.y+50,10,BLUE);
            }

            if (Debug::HasFlags(Debug::DRAW_BOUNDING_BOX)){
                // x,y,w,h
                auto bounds = renderer.GetBoundingBox(position,rotation);
                DrawRectangleLinesEx(bounds,1,BLUE);
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
        entityRegistry.emplace<Transform>(id);
//        entityRegistry.emplace<TagComponent>(id, "Object");
        m_EntityIds.push_back(id);
        return id;
    }


    void Scene::DrawUI() {

    }


}












