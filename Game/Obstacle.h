//
// Created by Bekir Gulestan on 3/15/24.
//
#pragma once

#include "Engine.h"
#include "GameObject.h"

class Obstacle: public RayEngine::GameObject{
public:
    Obstacle(Vector2 position, Vector2 size){
//        this->GetPhysics().SetPosition(position);
//        this->GetPhysics().SetMesh(new PhyRectangleMesh(size.x, size.y));
//
//
//        this->GetPhysics().SetMass(10.0f);
//        this->GetPhysics().SetGrounded(true);
    }


    void Update() override {
        // do nothing
    }


    void Draw() override {
//        Vector2 position = this->GetPhysics().GetPosition();
//        PhyMesh *mesh = this->GetPhysics().GetMesh();
//        float rotation = this->GetPhysics().GetRotation();
//
//        auto indices = mesh->GetIndices();
//        auto vertices = mesh->GetVertices();
//
//
//
//        for ( auto [v1,v2,v3] : indices){
//
//            Vector2 v1_world = Vector2Add(Vector2Rotate(v1,rotation) , position);
//            Vector2 v2_world = Vector2Add(Vector2Rotate(v2,rotation) , position);
//            Vector2 v3_world = Vector2Add(Vector2Rotate(v3,rotation) , position);
//
//            DrawTriangle(v1_world,v2_world,v3_world, RED);
//        }
    }

    void DrawUI() override {
    }


};