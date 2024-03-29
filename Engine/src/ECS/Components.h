//
// Created by Bekir Gulestan on 3/23/24.
//

#pragma once

#include "raylib.h"
#include "Entity.h"
#include "Mesh.h"
#include "Rotation.h"

#warning "This file is not used in the project"

namespace RayEngine {

    struct TagComponent {
        std::string tag;

        TagComponent() = default;
        TagComponent(const TagComponent&) = default;
        explicit TagComponent(const std::string& tag) : tag(tag) {}
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



