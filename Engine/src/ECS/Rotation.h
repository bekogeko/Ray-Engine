//
// Created by Bekir Gulestan on 3/28/24.
//

#pragma once
#include "raylib.h"

struct Rotation {

    // rotation in radians
    float GetRadians() const {
        return rotation * DEG2RAD;
    }

    void SetRadians(float radians) {
        rotation = radians * RAD2DEG;

        Normalize();
    }

    // rhs is in degrees
    Rotation& operator+=(const Rotation& rhs) {
        rotation += rhs.rotation;

        Normalize();
        return *this;
    }

    // rhs is in degrees
    Rotation& operator-=(const Rotation& rhs) {
        rotation -= rhs.rotation;

        Normalize();
        return *this;
    }

    // rhs is in degrees
    Rotation& operator+=(const float& rhs) {
        rotation += rhs;

        Normalize();
        return *this;
    }

    // rhs is in degrees
    Rotation& operator-=(const float& rhs) {
        rotation -= rhs;
        Normalize();
        return *this;
    }

    // rhs is in degrees
    Rotation& operator*=(const float& rhs) {
        rotation *= rhs;
        Normalize();
        return *this;
    }

    // rhs is in degrees
    Rotation& operator=(const float& rhs) {
        rotation = rhs;
        Normalize();
        return *this;
    }

    // float cast
    operator float() const {
        return rotation;
    }

private:
    void Normalize() {
        rotation = fmod(rotation, 360.0f);
    }
    float rotation = 0.0f;
};
