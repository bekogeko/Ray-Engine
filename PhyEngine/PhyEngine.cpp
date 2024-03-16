//
// Created by Bekir Gulestan on 3/15/24.
//

#include "PhyEngine.h"
#include "raymath.h"
#include <map>

void PhyEngine::UpdatePhysics() {
    // Apply forces
    for (std::tuple<PhyObject,Vector2> &forceCall: getInstance().m_ForceQueue) {
        PhyObject &object = std::get<0>(forceCall);
        Vector2 &force = std::get<1>(forceCall);
        object.ApplyForce(force);
    }

    // Apply Gravity
    for (PhyObject* object: getInstance().m_Objects) {
        auto acceleration = object->GetAcceleration();
        object->SetAcceleration({acceleration.x,acceleration.y+ 9.8f * object->GetMass() });
    }

    // Apply an impulse to the object in Newtons
    // I = F * t
    // it will add immediate velocity to the object
    // it is used for collision response
    // it is used for jump
    // it is used for knockback
    for (std::tuple<PhyObject,Vector2> &impulseCall: getInstance().m_ImpulseQueue) {
        PhyObject &object = std::get<0>(impulseCall);
        Vector2 &impulse = std::get<1>(impulseCall);

        object.ApplyImpulse(impulse);
    }

    // Clear the force and impulse queues
    getInstance().m_ForceQueue.clear();
    getInstance().m_ImpulseQueue.clear();


    // Update the physics
    for (PhyObject* object: getInstance().m_Objects) {
        object->UpdatePhysics();
    }

    // Check for collisions
    // Broad phase
    // - Find Potential Collisions
    // Narrow phase
    // - Check for collisions
    // Solution phase
    // - Resolve collisions

    std::vector<std::tuple<PhyObject*,PhyObject*>> potentialCollisions;

    // xStart, <xEnd,PhyObject*>
    std::map<int,std::tuple<int,PhyObject*>> overlap_map_x;

    // do broad phase on X axis
    for(auto obj: getInstance().m_Objects){
        Rectangle bounds = obj->GetBounds();

        int xStart = bounds.x;
        int xEnd = bounds.x + bounds.width;

        overlap_map_x[xStart] = std::make_tuple(xEnd,obj);
    }


    bool isFirst = true;
    int prevXEnd = 0;
    PhyObject* prevObj = nullptr;

    // go over the overlap map and check for potential collisions
    for(auto& [xStart, data]: overlap_map_x){

        auto& [xEnd, obj] = data;

        if(isFirst){
            isFirst = false;
            prevXEnd = xEnd;
            prevObj = obj;
            continue;
        }

        if(xStart < prevXEnd){
            potentialCollisions.push_back(std::make_tuple(obj,prevObj));
        }

        prevXEnd = xEnd;
    }

    // yStart, <yEnd,PhyObject*>
    std::map<int,std::tuple<int,PhyObject*>> overlap_map_y;

    // do broad phase on Y axis
    for(auto obj: getInstance().m_Objects){
        Rectangle bounds = obj->GetBounds();

        int yStart = bounds.y;
        int yEnd = bounds.y + bounds.height;

        overlap_map_y[yStart] = std::make_tuple(yEnd,obj);
    }

    isFirst = true;
    int prevYEnd = 0;
    prevObj = nullptr;

    // go over the overlap map and check for potential collisions
    for(auto& [yStart, data]: overlap_map_y){

        auto& [yEnd, obj] = data;

        if(isFirst){
            isFirst = false;
            prevYEnd = yEnd;
            prevObj = obj;
            continue;
        }

        if(yStart < prevYEnd){
            potentialCollisions.push_back(std::make_tuple(obj,prevObj));
        }

        prevYEnd = yEnd;
    }

    // narrow phase
    for(auto& [obj1,obj2]: potentialCollisions){
        if(CheckCollisionRecs(obj1->GetBounds(),obj2->GetBounds())){

            obj1->SetPosition(obj1->GetLastPosition());
            obj2->SetPosition(obj2->GetLastPosition());

            obj1->SetVelocity({0,0});
            obj2->SetVelocity({0,0});

            if(obj1->OnCollision != nullptr)
                obj1->OnCollision(*obj2);
            if(obj2->OnCollision != nullptr)
                obj2->OnCollision(*obj1);
        }
    }

    // Solution phase
//    for(auto& [obj1,obj2]: potentialCollisions){
//        // set position to the previous position
//        obj1->SetPosition(obj1->GetLastPosition());
//        obj2->SetPosition(obj2->GetLastPosition());
//
//    }






}

void PhyEngine::AddObject(PhyObject& collider) {
    getInstance().m_Objects.push_back(&collider);
}