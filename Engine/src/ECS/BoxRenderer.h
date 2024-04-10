//
// Created by Bekir Gulestan on 3/28/24.
//

#pragma once
#include "Mesh.h"

namespace RayEngine {

    struct BoxRenderer: RayEngine::Mesh{
    private:
        Vector2 size;
        Color color = RED;
    public:

        BoxRenderer(float width, float height) : size({width, height}) {

            this->vertexCount = 4;
            this->triangleCount = 2;

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

        Rectangle GetBoundingBox(Vector2 position, Rotation rotation) const override{
            // rotation happens around the center of the box
            // bounding box contains the rotated box
            // bounding box might be bigger than the box itself (most of the time)

            // get the half size of the box
            Vector2 halfSize = Vector2Divide(this->size, {2, 2});

            // get the corners of the box
            Vector2 topLeft = Vector2Add(position, Vector2Rotate(Vector2Negate(halfSize), rotation.GetRadians()));
            Vector2 topRight = Vector2Add(position, Vector2Rotate({halfSize.x, -halfSize.y}, rotation.GetRadians()));
            Vector2 bottomLeft = Vector2Add(position, Vector2Rotate({-halfSize.x, halfSize.y}, rotation.GetRadians()));
            Vector2 bottomRight = Vector2Add(position, Vector2Rotate(halfSize, rotation.GetRadians()));

            // get the min and max of the corners
            float minX = std::min({topLeft.x, topRight.x, bottomLeft.x, bottomRight.x});
            float minY = std::min({topLeft.y, topRight.y, bottomLeft.y, bottomRight.y});

            float maxX = std::max({topLeft.x, topRight.x, bottomLeft.x, bottomRight.x});
            float maxY = std::max({topLeft.y, topRight.y, bottomLeft.y, bottomRight.y});

            return {minX, minY, maxX - minX, maxY - minY};

        }

        std::vector<std::tuple<Vector2, Vector2>> GetFaces() const override{
            std::vector<std::tuple<Vector2, Vector2>> faces;

            faces.emplace_back(this->vertices[0], this->vertices[1]);
            faces.emplace_back(this->vertices[1], this->vertices[2]);
            faces.emplace_back(this->vertices[2], this->vertices[3]);
            faces.emplace_back(this->vertices[3], this->vertices[0]);

            return faces;
        }

        Vector2 GetSize() const {
            return size;
        }

        void SetColor(int r, int g, int b, int a){
            this->color = {static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b), static_cast<unsigned char>(a)};
        }

        inline Color GetColor() const {
            return color;
        }
    };
}