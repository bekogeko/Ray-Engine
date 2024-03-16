//
// Created by Bekir Gulestan on 3/16/24.
//

#pragma once


#include <vector>
#include "raylib.h"
#include "raymath.h"

class PhyMesh{

protected:
    int triangleCount;
    int vertexCount;

    std::vector<Vector2> vertices;
    std::vector<Vector2> normals;

    std::vector<std::tuple<Vector2,Vector2,Vector2>> indices;


public:
    // Returns face normals of the mesh in world space
    virtual std::vector<Vector2> GetNormals(float meshRotation) = 0;

    // Returns the vertices of the mesh in world space
    virtual std::vector<Vector2> GetVertices(Vector2 position, float rotation) = 0;

    // Returns the vertices of the mesh in local space
    virtual std::vector<Vector2> GetLocalVertices() const = 0;

    // Returns the indices of the mesh
    virtual std::vector<std::tuple<Vector2,Vector2,Vector2>> GetIndices() = 0;

    // Returns the triangle count of the mesh
    int GetTriangleCount() const {
        return triangleCount;
    }

    static Vector2 TransformPoint(Vector2 point, Vector2 position, float rotation){
        return Vector2Add(Vector2Rotate(point, rotation), position);
    }


};
