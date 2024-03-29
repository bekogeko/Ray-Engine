//
// Created by Bekir Gulestan on 3/28/24.
//

#pragma once
#include "Mesh.h"

namespace RayEngine {

    struct BoxRenderer: RayEngine::Mesh{
    private:
        Vector2 size;
        Color color = WHITE;
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
            // Get the bounding box of the rectangle with the given position and rotation angle (in radians in the center)

            float minX = INFINITY;
            float minY = INFINITY;

            float maxX = -INFINITY;
            float maxY = -INFINITY;

            for (auto &v: this->vertices){
                Vector2 rotated = Vector2Rotate(v, rotation.GetRadians());
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