//
// Created by Bekir Gulestan on 3/16/24.
//

#pragma once

#include "PhyObject.h"

class Entity
{
private:
    PhyObject m_Physics;

public:

    virtual void Init() {};
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void DrawUI() {};

    PhyObject& GetPhysics(){
        return m_Physics;
    }
};
