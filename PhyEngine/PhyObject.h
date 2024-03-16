//
// Created by Bekir Gulestan on 3/16/24.
//

#pragma once

// This is for MACOS only
#include <algorithm>

#include "raylib.h"
#include "PhyMesh.h"
#include "raymath.h"

class PhyObject {
private:
    float rotation=0.0f;
    float rotationSpeed = 0.0f;

    std::shared_ptr<PhyMesh> mesh;
    float mass;

    Vector2 position;
    Vector2 lastPosition;

    Vector2 velocity{0,0};
    Vector2 acceleration{0,0};

    bool isGrounded = false;
public:
    // collision callback function pointer
     std::function<void(PhyObject)> OnCollision = nullptr;

    explicit PhyObject();


    Vector2 SetAcceleration(Vector2 newAcceleration){
        acceleration = newAcceleration;
    }

    Vector2 GetAcceleration() const{
        return acceleration;
    }

    Vector2 GetLastPosition() const {
        return lastPosition;
    }

    Vector2 GetPosition() const {
        return position;
    }
    void SetPosition(Vector2 newPosition){
        position = newPosition;
        lastPosition = newPosition;
    }

    void SetRotation(float newRotation){
        rotation = newRotation;
    }
    float GetRotation() const{
        return rotation;
    }

    void SetMesh(PhyMesh* newMesh){
        mesh.reset(newMesh);
    }




    PhyMesh* GetMesh() const{
        return mesh.get();
    }





    void SetMass(float newMass);
    float GetMass() const;
    void SetGrounded(bool grounded){
        isGrounded = grounded;
    }
    bool GetGrounded() const{
        return isGrounded;
    }
    Vector2 GetVelocity();
    void SetVelocity(Vector2 velocity);




    // Apply an impulse to the object in Newtons
    // I = F * t
    // it will add immediate velocity to the object
    // it is used for collision response
    // it is used for jump
    // it is used for knockback
    void ApplyImpulse(Vector2 impulse) {
        velocity.x += impulse.x / mass;
        velocity.y += impulse.y / mass;
    };

    // Apply a force to the object in Newtons
    // F = ma
    // it will add immediate acceleration to the object
    void ApplyForce(Vector2 force) {
        acceleration.x += force.x / mass;
        acceleration.y += force.y / mass;
    };



    void UpdatePhysics();

    // Bounds of the object
    // it is used for broad phase collision detection
    Rectangle GetBounds() const {
        return mesh.get()->GetBoundingBox(this->position, this->rotation);
    }




};