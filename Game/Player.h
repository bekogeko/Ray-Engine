//
// Created by Bekir Gulestan on 3/23/24.
//
#pragma once

#include "entt/entt.hpp"
#include "RayEngine.h"

class Player: public RayEngine::Entity{

protected:

    void Start() override {
        auto& renderer = AddComponent<RayEngine::BoxRenderer>(60,50);
        renderer.SetColor(0,0,255,255);

        AddComponent<RayEngine::PhysicsBody>(100);

        auto &transform = AddComponent<RayEngine::Transform>();
        transform.rotation = 35.0f;
    }

    void Update(float deltaTime) override {
        auto& transform = GetComponent<RayEngine::Transform>();
        auto& physicsBody = GetComponent<RayEngine::PhysicsBody>();


        if(IsKeyDown(KEY_E)){
            physicsBody.ApplyTorque(100);
        }
        if(IsKeyDown(KEY_Q)){
            physicsBody.ApplyTorque(-100);
        }


        if(IsKeyDown(KEY_W)){
            physicsBody.ApplyImpulse(Vector2{0,-100});
        }
        if(IsKeyDown(KEY_S)){
            physicsBody.ApplyImpulse(Vector2{0,100});
        }
        if(IsKeyDown(KEY_A)){
            physicsBody.ApplyImpulse(Vector2{-100,0});
        }
        if(IsKeyDown(KEY_D)){
            physicsBody.ApplyImpulse(Vector2{100,0});
        }
    }

public:
    Player() = default;
    ~Player() override {
        std::cout << "Player destroyed..." << std::endl;
    };
};