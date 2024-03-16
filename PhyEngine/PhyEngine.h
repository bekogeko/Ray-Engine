//
// Created by Bekir Gulestan on 3/15/24.
//

#pragma once

#include "raylib.h"
#include "PhyObject.h"
#include <vector>

// - Move the objects apart
// - Apply forces
// - Apply impulses
// - Apply friction
// - Apply restitution
// - Apply damping
// - Apply gravity
// - Apply air resistance
// - Apply drag
// - Apply torque
// - Apply angular velocity
class PhyEngine {


public:
    static void AddObject(PhyObject& collider);

//    static bool CheckWorldCollision(Rectangle collider) {
//        for (auto &c: getInstance().m_Objects) {
//            if (!isColliding(collider, c))
//                continue;
//
//            return true;
//        }
//        return false;
//    }

    static void UpdatePhysics();

//    static bool isColliding(Rectangle a, Rectangle b){
//        return a.x + a.width >= b.x &&
//               b.x + b.width >= a.x &&
//               a.y + a.height >= b.y &&
//               b.y + b.height >= a.y;
//    }

    static void SubmitForce(PhyObject object, Vector2 force){
        getInstance().m_ForceQueue.emplace_back(object, force);
    }

    static void SubmitImpulse(PhyObject object, Vector2 impulse){
        getInstance().m_ImpulseQueue.emplace_back(object, impulse);
    }

private:
    std::vector<PhyObject*> m_Objects;

    std::vector<std::tuple<PhyObject,Vector2>> m_ForceQueue;
    std::vector<std::tuple<PhyObject,Vector2>> m_ImpulseQueue;



    static PhyEngine& getInstance(){
        static PhyEngine instance = PhyEngine();
        return instance;
    }

};


