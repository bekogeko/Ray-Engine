//
// Created by Bekir Gulestan on 3/26/24.
//

#pragma once

#include "raylib.h"

namespace RayEngine {

    enum class ColliderType {
        Box,
        Circle,
        Polygon
    };

    struct PhysicsBody {
        float mass = 1.0f;
        float restitution = 0.0f;
        float rotationalVelocity = 0.0f;
        float density = 1.0f;

        ColliderType colliderType;

        Vector2 velocity = {0,0};
        Vector2 acceleration = {0,0};

        PhysicsBody(float mass): mass(mass) {}

        void ApplyForce(Vector2 force){
            acceleration.x += (force.x/mass) * GetFrameTime();
            acceleration.y += (force.y/mass) * GetFrameTime();
        }

        void ApplyImpulse(Vector2 impulse){
            velocity = Vector2Add(velocity, Vector2Scale(impulse, 1.0f/mass));
        }

        void ApplyTorque(float torque){
            rotationalVelocity +=(torque/mass)* GetFrameTime();
        }
    };
}
