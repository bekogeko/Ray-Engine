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
        if(CheckMeshCollision(obj1,obj2)){
            // collision detected
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

    potentialCollisions.clear();


}

void PhyEngine::AddObject(PhyObject& collider) {
    getInstance().m_Objects.push_back(&collider);
}

bool PhyEngine::CheckMeshCollision(PhyObject *object1, PhyObject *object2) {
    // Mesh to Mesh Collision
    // - SAT (Separating Axis Theorem)
    // - GJK (Gilbert-Johnson-Keerthi)
    // - EPA (Expanding Polytope Algorithm)
    // - MPR (Minkowski Portal Refinement)

    // We will use SAT for now
    auto vertices1 = object1->GetMesh()->GetVertices();
    auto vertices2 = object2->GetMesh()->GetVertices();

    std::vector<Vector2> worldVertices1;
    std::vector<Vector2> worldVertices2;

    for (auto vertex: vertices1){
        worldVertices1.push_back(Vector2Add(Vector2Rotate(vertex,object1->GetRotation()),object1->GetPosition()));
    }

    for (auto vertex: vertices2){
        worldVertices2.push_back(Vector2Add(Vector2Rotate(vertex,object2->GetRotation()),object2->GetPosition()));
    }

    for (int shape = 0; shape < 2; shape++) {
        if (shape ==1){
            std::swap(worldVertices1,worldVertices2);
        }

        for (int a = 0; a < worldVertices1.size(); ++a) {
            int b = (a + 1) % worldVertices1.size();
            Vector2 axisProj = {
                    -(worldVertices1[b].y - worldVertices1[a].y),
                    worldVertices1[b].x - worldVertices1[a].x
            };

            float min_r1 = INFINITY;
            float max_r1 = -INFINITY;

            for (int p = 0; p < worldVertices1.size();p++) {
                float q = Vector2DotProduct(worldVertices1[p], axisProj);

                min_r1 = fmin(min_r1, q);
                max_r1 = fmax(max_r1, q);
            }

            float min_r2 = INFINITY;
            float max_r2 = -INFINITY;

            for (int p = 0; p < worldVertices2.size();p++) {
                float q = Vector2DotProduct(worldVertices2[p], axisProj);

                min_r2 = fmin(min_r2, q);
                max_r2 = fmax(max_r2, q);
            }

            if (!(max_r2>=min_r1 && max_r1>=min_r2)){
                return false;
            }
        }
    }
    return true;
}