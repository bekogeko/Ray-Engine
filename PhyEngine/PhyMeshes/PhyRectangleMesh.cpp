//
// Created by Bekir Gulestan on 3/16/24.
//

#include "PhyRectangleMesh.h"


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
    return {position.x - width/2, position.y - height/2, width, height};
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
