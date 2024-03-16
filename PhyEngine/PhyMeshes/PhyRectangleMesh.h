//
// Created by Bekir Gulestan on 3/16/24.
//

#pragma once

#include "raylib.h"
#include "raymath.h"
#include "../PhyMesh.h"

class PhyRectangleMesh: public PhyMesh {

private:
    float m_width;
    float m_height;

    Vector2 TransformPoint(Vector2 point, Vector2 position, float rotation){
        return Vector2Add(Vector2Rotate(point, rotation), position);
    }
public:
    PhyRectangleMesh(int width, int height) {
        this->m_width = width;
        this->m_height = height;

        // Set the vertices of the rectangle
        this->triangleCount = 2;
        this->vertexCount = 4;


        this->vertices = {
            // Positions
            // Bottom-left
            {-0.5f * m_width , -0.5f * m_height},
            // Bottom-right
            {0.5f * m_width, -0.5f * m_height},
            // Top-right
            {0.5f * m_width, 0.5f * m_height},
            // Top-left
            {-0.5f * m_width, 0.5f * m_height}
        };

        this->normals = {
            // Normals
            // Bottom
            {0.0f, -1.0f},
            // Right
            {1.0f, 0.0f},
            // Top
            {0.0f, 1.0f},
            // Left
            {-1.0f, 0.0f}
        };


    }


    // Returns face normals of the mesh in world space
    std::vector<Vector2> GetNormals(float meshRotation) override  {
        std::vector<Vector2> worldNormals;

        for (auto normal : normals) {
            worldNormals.push_back(Vector2Rotate(normal, meshRotation));
        }

        return worldNormals;
    }

    std::vector<Vector2> GetVertices(Vector2 position, float rotation) override {

        std::vector<Vector2> worldVertices;

        for (auto vertex : vertices) {
            worldVertices.push_back(PhyRectangleMesh::TransformPoint(vertex, position ,rotation));
        }

        return worldVertices ;
    }

    std::vector<Vector2> GetLocalVertices() const override {
        return vertices;
    }


    std::vector<std::tuple<Vector2, Vector2, Vector2>> GetIndices() override {
        return {
            {vertices[0], vertices[3], vertices[2]},
            {vertices[0], vertices[2], vertices[1]}
        };
    }


    Rectangle GetBoundingBox(Vector2 position, float rotation) override {

        // Get the world vertices
        std::vector<Vector2> worldVertices = GetVertices(position, rotation);

        // Find the min and max x and y values
        float minX = worldVertices[0].x;
        float maxX = worldVertices[0].x;
        float minY = worldVertices[0].y;
        float maxY = worldVertices[0].y;

        for (auto vertex : worldVertices) {
            if (vertex.x < minX) {
                minX = vertex.x;
            }
            if (vertex.x > maxX) {
                maxX = vertex.x;
            }
            if (vertex.y < minY) {
                minY = vertex.y;
            }
            if (vertex.y > maxY) {
                maxY = vertex.y;
            }
        }

        return {minX, minY, maxX - minX, maxY - minY};
    }


};

