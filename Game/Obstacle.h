//
// Created by Bekir Gulestan on 3/28/24.
//

#pragma once

#include "RayEngine.h"

class Obstacle: public RayEngine::Entity{

    void Start() override {
        AddComponent<RayEngine::BoxRenderer>(50,50);
        AddComponent<RayEngine::PhysicsBody>(100);

        auto &transform = AddComponent<RayEngine::Transform>();
        transform.rotation = 35.0f;
    }

    void Update(float deltaTime) override {

    }

};