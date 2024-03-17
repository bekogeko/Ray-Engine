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

    // vertices and normals of the mesh
    std::vector<Vector2> vertices;


    // line normals of the mesh in local space
    std::vector<Vector2> normals;

    // index of the vertices that make up a triangle
    std::vector<std::tuple<Vector2,Vector2,Vector2>> indices;


public:
    // virtual destructor
    virtual ~PhyMesh() {};


    // Returns the bounding box of the mesh
    virtual Rectangle GetBoundingBox(Vector2 position, float rotation) = 0;

    // gives the faces of the mesh in local space
    virtual std::vector<std::tuple<Vector2,Vector2>> GetFaces() const = 0;




    // Returns the normals of every line in the mesh in local space
    std::vector<Vector2> GetNormals() const {
        return normals;
    }

    // Returns the vertices of the mesh in local space
    std::vector<Vector2> GetVertices() const {
        return vertices;
    };

    // Returns the indices of the mesh
    // each tuple contains the vertices of a triangle
    // in counter-clockwise order
    std::vector<std::tuple<Vector2,Vector2,Vector2>> GetIndices() const {
        return indices;
    };


    // Returns the triangle count of the mesh
    int GetTriangleCount() const {
        return triangleCount;
    }
};
