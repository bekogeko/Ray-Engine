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
        this->GetPhysics().SetMesh(new PhyRectangleMesh(24, 64));


        // set OnCollision fn pointer to point OnCollide callback
        // using std::bind to bind the member function to the class instance
        // it wil
        this->GetPhysics().OnCollision = std::bind(&Player::OnCollide, this, std::placeholders::_1);

    }




    void Draw(){
        Vector2 position = this->GetPhysics().GetPosition();

        PhyMesh *mesh = this->GetPhysics().GetMesh();
        float rotation = this->GetPhysics().GetRotation();
        float meshWidth = mesh->GetBoundingBox(position, rotation).width;
        float meshHeight = mesh->GetBoundingBox(position, rotation).height;


        auto indices = mesh->GetIndices();
        auto vertices = mesh->GetVertices();
        auto normals = mesh->GetNormals();

        for ( auto [v1,v2,v3] : indices){

            Vector2 v1_world = Vector2Add(Vector2Rotate(v1,rotation) , position);
            Vector2 v2_world = Vector2Add(Vector2Rotate(v2,rotation) , position);
            Vector2 v3_world = Vector2Add(Vector2Rotate(v3,rotation) , position);

            DrawTriangle(v1_world,v2_world,v3_world, DARKGRAY);
        }

//        // Draw the normals of the player
//        // Bottom Normal Visualizer
//        // Distance Vector from the center of the player to the bottom of the player
//        // takes the rotation of the player into account
//        Vector2 bottomPoint = Vector2Add(Vector2Rotate({0, meshHeight/2}, rotation), position);
//        Vector2 bottomNormal = Vector2Normalize(Vector2Rotate(normals[0], rotation));
//        bottomNormal = Vector2Scale(bottomNormal, 10);
//        DrawLineEx(bottomPoint, Vector2Subtract(bottomPoint, bottomNormal), 2, BLUE);
//
//
//
//        // Right Normal Visualizer
//        Vector2 rightPoint = Vector2Add(Vector2Rotate({meshWidth/2, 0}, rotation), position);
//        Vector2 rightNormal = Vector2Normalize(Vector2Rotate(normals[1], rotation));
//        rightNormal = Vector2Scale(rightNormal, 10);
//        DrawLineEx(rightPoint, Vector2Add(rightPoint, rightNormal), 2, BLUE);
//
//
//        // Top Normal Visualizer
//        // Distance Vector from the center of the player to the top of the player
//        // takes the rotation of the player into account
//        Vector2 topPoint = Vector2Add(Vector2Rotate({0, -meshHeight/2}, rotation), position);
//
//        // Add Normalized vector to the top point to get the middle point of the top face
//        Vector2 topNormal = Vector2Normalize(Vector2Rotate(normals[2], rotation));
//        topNormal = Vector2Scale(topNormal, 10);
//        DrawLineEx(topPoint, Vector2Subtract(topPoint, topNormal), 2, BLUE);
//
//        // Left Normal Visualizer
//        Vector2 leftPoint = Vector2Add(Vector2Rotate({-meshWidth/2, 0}, rotation), position);
//        Vector2 leftNormal = Vector2Normalize(Vector2Rotate(normals[3], rotation));
//        leftNormal = Vector2Scale(leftNormal, 10);
//        DrawLineEx(leftPoint, Vector2Add(leftPoint, leftNormal), 2, BLUE);








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
//            this->GetPhysics().ApplyForce({0, 300.0f});
        }

        if(IsKeyDown(KEY_E)){
            this->GetPhysics().SetRotation(this->GetPhysics().GetRotation() + 0.01f);

        }


        if (IsKeyDown(KEY_SPACE) ){
            this->GetPhysics().ApplyForce({0,-300.0f * this->GetPhysics().GetMass()});
        }
    }


    void DrawUI() {
        Vector2 position = this->GetPhysics().GetPosition();
        // accleeration
        // velocity
        // position
        DrawText(TextFormat("Player's Acceleration: %.1f x, %.1f y",this->GetPhysics().GetAcceleration().x, this->GetPhysics().GetAcceleration().y) , 10, 20, 20, LIGHTGRAY);
        DrawText(TextFormat("Player's Speed: %.1f x, %.1f y",this->GetPhysics().GetVelocity().x, this->GetPhysics().GetVelocity().y) , 10, 40, 20, LIGHTGRAY);
        DrawText(TextFormat("Player's Position: %.1f x, %.1f y",position.x, position.y) , 10, 60, 20, LIGHTGRAY);

    }

    void OnCollide(PhyObject other)  {
        isColliding = true;
    }

private:
    bool isColliding = false;
};
