//
// Created by Bekir Gulestan on 3/16/24.
//

#include "PhyRectangleMesh.h"
#include "../Debug.h"


PhyRectangleMesh::PhyRectangleMesh(float width, float height) {

    this->width = width;
    this->height = height;

    this->triangleCount = 2;
    this->vertexCount = 4;

    // in counter-clockwise order
    // bottom left
    this->vertices.push_back({-width/2, -height/2});
    // bottom right
    this->vertices.push_back({width/2, -height/2});
    // top right
    this->vertices.push_back({width/2, height/2});
    // top left
    this->vertices.push_back({-width/2, height/2});

    // top right, bottom right, bottom left
    this->indices.emplace_back(this->vertices[2], this->vertices[1], this->vertices[0]);
    // bottom left, top left, top right
    this->indices.emplace_back(this->vertices[0], this->vertices[3], this->vertices[2]);

    // Bottom Face Normal
    this->normals.push_back({0, -1});

    // Right Face Normal
    this->normals.push_back({1, 0});

    // Top Face Normal
    this->normals.push_back({0, 1});
    // Left Face Normal
    this->normals.push_back({-1, 0});


}

Rectangle PhyRectangleMesh::GetBoundingBox(Vector2 position, float rotation) {

    // Get the bounding box of the rectangle with the given position and rotation angle (in radians in center)

    float minX = INFINITY;
    float minY = INFINITY;

    float maxX = -INFINITY;
    float maxY = -INFINITY;

    for (auto &v: this->vertices){
        Vector2 rotated = Vector2Rotate(v, rotation);
        Vector2 translated = Vector2Add(rotated, position);

        if (translated.x < minX)
            minX = translated.x;
        if (translated.x > maxX)
            maxX = translated.x;

        if (translated.y < minY)
            minY = translated.y;
        if (translated.y > maxY)
            maxY = translated.y;
    }

    return {minX, minY, maxX - minX, maxY - minY};
}

std::vector<std::tuple<Vector2, Vector2>> PhyRectangleMesh::GetFaces() const {
    std::vector<std::tuple<Vector2, Vector2>> faces;

    faces.emplace_back(this->vertices[0], this->vertices[1]);
    faces.emplace_back(this->vertices[1], this->vertices[2]);
    faces.emplace_back(this->vertices[2], this->vertices[3]);
    faces.emplace_back(this->vertices[3], this->vertices[0]);

    return faces;
}

PhyRectangleMesh::~PhyRectangleMesh() {
}

void PhyRectangleMesh::DrawDebug(Vector2 position, float rotation) const {

    if(Debug::HasFlags(Debug::DRAW_NORMALS)){

        // Bottom Face Normal Visualizer
        Vector2 bottomPoint = Vector2Add(Vector2Rotate({0, height/2}, rotation), position);
        Vector2 bottomNormal = Vector2Normalize(Vector2Rotate(normals[0], rotation));
        bottomNormal = Vector2Scale(bottomNormal, 10);
        DrawLineEx(bottomPoint, Vector2Subtract(bottomPoint, bottomNormal), 2, BLUE);

        // Right Face Normal Visualizer
        Vector2 rightPoint = Vector2Add(Vector2Rotate({width/2, 0}, rotation), position);
        Vector2 rightNormal = Vector2Normalize(Vector2Rotate(normals[1], rotation));
        rightNormal = Vector2Scale(rightNormal, 10);
        DrawLineEx(rightPoint, Vector2Add(rightPoint, rightNormal), 2, BLUE);

        // Top Face Normal Visualizer
        Vector2 topPoint = Vector2Add(Vector2Rotate({0, -height/2}, rotation), position);
        Vector2 topNormal = Vector2Normalize(Vector2Rotate(normals[2], rotation));
        topNormal = Vector2Scale(topNormal, 10);
        DrawLineEx(topPoint, Vector2Subtract(topPoint, topNormal), 2, BLUE);

        // Left Face Normal Visualizer
        Vector2 leftPoint = Vector2Add(Vector2Rotate({-width/2, 0}, rotation), position);
        Vector2 leftNormal = Vector2Normalize(Vector2Rotate(normals[3], rotation));
        leftNormal = Vector2Scale(leftNormal, 10);
        DrawLineEx(leftPoint, Vector2Add(leftPoint, leftNormal), 2, BLUE);
    }




}
