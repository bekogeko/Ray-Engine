//
// Created by Bekir Gulestan on 3/15/24.
//
#pragma once

#include "raylib.h"

class Player {
public:

    Vector2 position;

    Vector2 velocity;
    Vector2 acceleration;

    explicit  Player(Vector2 position):
        position(position),
        velocity({0, 0}),
        acceleration({0, 0}),
        m_Collider({position.x, position.y, 24, 64}) {}



        void Draw(){
            DrawRectangleRec(m_Collider, RED);
        }

        void Update(){
            velocity.x += acceleration.x;
            velocity.y += acceleration.y;

            position.x += velocity.x;
            position.y += velocity.y;

            m_Collider.x = position.x;
            m_Collider.y = position.y;
        }

private:

    Rectangle m_Collider;
};
