//
// Created by Bekir Gulestan on 3/28/24.
//

#pragma once

#include "RayEngine.h"

class Obstacle: public RayEngine::Entity{

private:
    Vector2 position;
    Vector2 size;
public:

    Obstacle(Vector2 position, Vector2 size): position(position), size(size){
        static int count = 0;
        m_Name = "Obstacle " + std::to_string(count++);
    }

    void Start() override {
        AddComponent<RayEngine::BoxRenderer>(size.x, size.y);
        AddComponent<RayEngine::PhysicsBody>(100);

        auto &transform = AddComponent<RayEngine::Transform>();
        transform.rotation = 35.0f;
        transform.position = position;
    }

    void Update(float deltaTime) override {

    }

};