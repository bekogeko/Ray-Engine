//
// Created by Bekir Gulestan on 3/23/24.
//
#pragma once

#include "entt/entt.hpp"
#include "RayEngine.h"

class Player: public RayEngine::Entity{

protected:

    void Start() override {
        AddComponent<RayEngine::BoxRenderer>(50,50);
        auto &transform = AddComponent<RayEngine::TransformComponent>();
        transform.rotation = 35.0f;
    }

    void Update(float deltaTime) override {
        auto& transform = GetComponent<RayEngine::TransformComponent>();
        if(IsKeyDown(KEY_W)){
            transform.rotation += 1.0f*deltaTime;
        }
    }

public:
    Player() = default;
    ~Player() override {
        std::cout << "Player destroyed..." << std::endl;
    };
};