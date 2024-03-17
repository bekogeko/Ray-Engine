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
    static void UpdatePhysics();

    static void SubmitForce(PhyObject object, Vector2 force){
        getInstance().m_ForceQueue.emplace_back(object, force);
    }

    static void SubmitImpulse(PhyObject object, Vector2 impulse){
        getInstance().m_ImpulseQueue.emplace_back(object, impulse);
    }

    static bool CheckMeshCollision(PhyObject* object1, PhyObject* object2);

private:
    std::vector<PhyObject*> m_Objects;

    std::vector<std::tuple<PhyObject,Vector2>> m_ForceQueue;
    std::vector<std::tuple<PhyObject,Vector2>> m_ImpulseQueue;



    static PhyEngine& getInstance(){
        static PhyEngine instance = PhyEngine();
        return instance;
    }

};


// Fast inverse square root
// https://en.wikipedia.org/wiki/Fast_inverse_square_root
// https://www.youtube.com/watch?v=p8u_k2LIZyo
static float q_rsqrt(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;                       // evil floating point bit level hacking
    i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
    // y = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return y;
}