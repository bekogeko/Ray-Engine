//
// Created by Bekir Gulestan on 3/28/24.
//

#pragma once

#include "Rotation.h"

namespace RayEngine {

    struct Transform{
        // the changes will be applied to these variables
        Vector2 position;
        // rotation in radians
        Rotation rotation;

        // reassign last position and rotation
        // if something goes wrong, we can revert back to the last position.
        // if we need to interpolate between the last and current position.
        // if everything is working fine, this function will be called at the end of the update
        void UpdateLast(){
            lastPosition = position;
            lastRotation = rotation;
        }

        inline Vector2 getLastPosition() const{
            return lastPosition;
        }

        inline float getLastRotation() const{
            return lastRotation;
        }


        Transform() = default;
        Transform(const Transform&) = default;
        explicit Transform(const Vector2& pos){
            position = pos;
            rotation = 0.0f;

            UpdateLast();
        }
    private:
        Vector2 lastPosition{};
        Rotation lastRotation{};
    };
}