//
// Created by Bekir Gulestan on 3/23/24.
//
#pragma once

class IComponent{
public:
    virtual void Start(RayEngine::Entity &e) {

    }

    virtual void Update(RayEngine::Entity &e, float deltaTime) {

    }
};

struct IRenderable{
public:
    virtual void Draw(RayEngine::Entity &e)=0;

    enum class RenderType{
        SPRITE,
        TEXT,
    };

    RenderType renderType = RenderType::SPRITE;

};