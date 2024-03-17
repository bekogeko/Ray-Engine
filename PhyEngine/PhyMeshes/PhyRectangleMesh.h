//
// Created by Bekir Gulestan on 3/16/24.
//

#pragma once

#include "raylib.h"
#include "../PhyMesh.h"

class PhyRectangleMesh: public PhyMesh {
public:

    PhyRectangleMesh(float width, float height);

    // used for board collision detection
    Rectangle GetBoundingBox(Vector2 position, float rotation) override;

    std::vector<std::tuple<Vector2, Vector2>> GetFaces() const override;

    ~PhyRectangleMesh() override;

private:
    float width;
    float height;

};

