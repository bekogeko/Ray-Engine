//
// Created by Bekir Gulestan on 3/16/24.
//

#include "PhyObject.h"
#include "PhyEngine.h"


PhyObject::PhyObject(): position({0,0}), mass(10.0f) {
    PhyEngine::AddObject(*this);
    // Set the default mesh to a square
//    this->mesh = nullptr;
}

void PhyObject::SetMass(float newMass) {
    mass = newMass;
}

float PhyObject::GetMass() const {
    return mass;
}

void PhyObject::SetVelocity(Vector2 velocity) {
    this->velocity = velocity;
}

Vector2 PhyObject::GetVelocity() {
    return velocity;
}

void PhyObject::UpdatePhysics() {
    if (isGrounded) {
        // Do not move in any direction if the object is grounded
        velocity.x = 0;
        velocity.y = 0;

        rotationSpeed = 0;

        return;
    }




    float frameTime = GetFrameTime();


    velocity.x += acceleration.x * frameTime;
    velocity.y += acceleration.y * frameTime;

    lastPosition = position;
    rotation += rotationSpeed * frameTime;

    position.x += velocity.x * frameTime;
    position.y += velocity.y * frameTime;

    acceleration.x = 0;
    acceleration.y = 0;

}