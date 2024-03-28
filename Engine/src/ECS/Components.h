//
// Created by Bekir Gulestan on 3/23/24.
//

#pragma once

#include "raylib.h"
#include "Entity.h"
#include "Mesh.h"

namespace RayEngine {
    struct TransformComponent{
        // the changes will be applied to these variables
        Vector2 position;
        float rotation;


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

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        explicit TransformComponent(const Vector2& pos){
            position = pos;
            rotation = 0.0f;

            UpdateLast();
        }
    private:
        Vector2 lastPosition{};
        float lastRotation{};
    };

    struct TagComponent {
        std::string tag;

        TagComponent() = default;
        TagComponent(const TagComponent&) = default;
        explicit TagComponent(const std::string& tag) : tag(tag) {}
    };


    struct BoxRenderer: RayEngine::Mesh{
    private:
        Vector2 size;
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
        Rectangle GetBoundingBox(Vector2 position, float rotation) const override{
            // Get the bounding box of the rectangle with the given position and rotation angle (in radians in the center)

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
    };

//    struct UIElement{
//        Vector2 position{0,0};
//        std::string text;
//        Color color{GRAY};
//        float fontSize = 20.0f;
//
//        UIElement() = default;
//        UIElement(const UIElement&) = default;
//        explicit UIElement(const Vector2& pos, std::string  text, const Color& color) : position(pos), text(std::move(text)), color(color), fontSize(20) {}
//    };






}



