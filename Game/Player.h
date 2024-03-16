//
// Created by Bekir Gulestan on 3/15/24.
//
#pragma once

#include "raylib.h"
#include "../PhyEngine/Entity.h"
#include "../PhyEngine/PhyMeshes/PhyRectangleMesh.h"


class Player : public Entity{
public:
    explicit  Player(float x, float y){

        // set the size, position, and mass of the player
//        this->GetPhysics().SetSize({24,64});
        this->GetPhysics().SetPosition({x,y});
        this->GetPhysics().SetMass(10.0f);

        // set the mesh of the player
        this->GetPhysics().SetMesh(new PhyRectangleMesh(24,64));


        // set OnCollision fn pointer to point OnCollide callback
        // using std::bind to bind the member function to the class instance
        // it wil
        this->GetPhysics().OnCollision = std::bind(&Player::OnCollide, this, std::placeholders::_1);

    }




    void Draw(){
        Vector2 position = this->GetPhysics().GetPosition();

        PhyMesh *mesh = this->GetPhysics().GetMesh();
        float rotation = this->GetPhysics().GetRotation();

        auto indices = mesh->GetIndices();

        for ( auto [v1,v2,v3] : indices){

            Vector2 v1_world = PhyMesh::TransformPoint(v1, position, rotation);
            Vector2 v2_world = PhyMesh::TransformPoint(v2, position, rotation);
            Vector2 v3_world = PhyMesh::TransformPoint(v3, position, rotation);

            DrawTriangle(v1_world,v2_world,v3_world, BLUE);
        }

    }


    void Update(){

        if (IsKeyDown(KEY_A)){
            this->GetPhysics().ApplyImpulse({-10.0f,0});
        }
        if (IsKeyDown(KEY_D)){
            this->GetPhysics().ApplyImpulse({10.0f,0});
        }

        if(IsKeyDown(KEY_S)){
            this->GetPhysics().ApplyImpulse({0, 10.0f});
        }

        if (IsKeyDown(KEY_SPACE) ){
            this->GetPhysics().ApplyImpulse({0, -10.0f});
        }
    }


    void DrawUI() {
        Vector2 position = this->GetPhysics().GetPosition();
        DrawText(TextFormat("Player's Speed: %.1f x, %.1f y",this->GetPhysics().GetVelocity().x, this->GetPhysics().GetVelocity().y) , 10, 40, 20, LIGHTGRAY);
        DrawText(TextFormat("Player's Position: %.1f x, %.1f y",position.x, position.y) , 10, 60, 20, LIGHTGRAY);
    }

    void OnCollide(PhyObject other)  {
        isColliding = true;
    }

private:
    bool isColliding = false;
};
