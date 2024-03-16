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
        object->ApplyForce({0, 9.8f * object->GetMass() });
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
    std::map<int,std::tuple<bool,PhyObject*>> shadows_on_x;
    std::map<int,std::tuple<bool,PhyObject*>> shadows_on_y;


//    for(auto obj: getInstance().m_Objects){
//        shadows_on_x[obj->GetPosition().x - (obj->GetSize().x/2)] = {true,obj};
//        shadows_on_x[obj->GetPosition().x + (obj->GetSize().x/2)] = {false,obj};
//
//        shadows_on_y[obj->GetPosition().y - (obj->GetSize().y/2)] = {true,obj};
//        shadows_on_y[obj->GetPosition().y + (obj->GetSize().y/2)] = {false,obj};
//    }
//
//    bool isStarted_X = false;
//    PhyObject* previousStart_X = nullptr;
//    // Check for potential collisions
//    for(auto [ posX, data]: shadows_on_x){
//
//        bool  is_start_entry = std::get<0>(data);
//        PhyObject* obj = std::get<1>(data);
//
//        if(isStarted_X){
//            if(is_start_entry){
//                potentialCollisions.push_back({previousStart_X,obj});
//                previousStart_X = obj;
//            }else{
//                isStarted_X = false;
//            }
//        }else{
//            if(is_start_entry){
//                isStarted_X = true;
//                previousStart_X = obj;
//            }
//        }
//    }
//
//    bool isStarted_Y = false;
//    PhyObject* previousStart_Y = nullptr;
//    // Check for potential collisions
//    for(auto [ posY, data]: shadows_on_y){
//
//        bool  is_start_entry = std::get<0>(data);
//        PhyObject* obj = std::get<1>(data);
//
//        if(isStarted_Y){
//            if(is_start_entry){
//                potentialCollisions.push_back({previousStart_Y,obj});
//                previousStart_Y = obj;
//            }else{
//                isStarted_Y = false;
//            }
//        }else{
//            if(is_start_entry){
//                isStarted_Y = true;
//                previousStart_Y = obj;
//            }
//        }
//    }
//
//
//
//
//
//
//    // Check for collisions
//    for (std::tuple<PhyObject*,PhyObject*> &potentialCollision: potentialCollisions) {
//        PhyObject* objectA = std::get<0>(potentialCollision);
//        PhyObject* objectB = std::get<1>(potentialCollision);
//
//        if(objectA->GetGrounded() && objectB->GetGrounded()){
//            continue;
//        }
//
//
//
//    }
//




}

void PhyEngine::AddObject(PhyObject& collider) {
    getInstance().m_Objects.push_back(&collider);
}