//
// Created by Bekir Gulestan on 3/15/24.
//
#pragma once

#include "raylib.h"
#include "../PhyEngine/Entity.h"

class Obstacle: public Entity{
public:
    Obstacle(Vector2 position, Vector2 size){
        this->GetPhysics().SetPosition(position);
        this->GetPhysics().SetMesh(new PhyRectangleMesh(size.x,size.y));


        this->GetPhysics().SetMass(10.0f);
        this->GetPhysics().SetGrounded(true);
    }


    void Update() override {
        // do nothing
    }


    void Draw() override {
        Vector2 position = this->GetPhysics().GetPosition();
        PhyMesh *mesh = this->GetPhysics().GetMesh();
        float rotation = this->GetPhysics().GetRotation();

        auto indices = mesh->GetIndices();
        auto vertices = mesh->GetVertices(position, rotation);

        for ( auto [v1,v2,v3] : indices){

            Vector2 v1_world = PhyMesh::TransformPoint(v1, position, rotation);
            Vector2 v2_world = PhyMesh::TransformPoint(v2, position, rotation);
            Vector2 v3_world = PhyMesh::TransformPoint(v3, position, rotation);

            DrawTriangle(v1_world,v2_world,v3_world, RED);
        }

        for (auto vertex : vertices) {


            DrawCircle(vertex.x, vertex.y,2, RED);
        }

    }






};