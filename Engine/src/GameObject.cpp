//
// Created by Bekir Gulestan on 3/16/24.
//

#include "GameObject.h"
#include "Engine.h"
#include "Debug.h"

namespace RayEngine
{
    GameObject::GameObject()
    {
        m_EntityId = Engine::CreateEntity();
    }

    void GameObject::DrawDebug()
    {
//
//
//            if(Debug::HasFlags(Debug::DRAW_ROTATION)){
//                // Get the position of the object
//                Vector2 position = m_Physics.GetPosition();
//
//                // Get the rotation of the object
//                float rotation = m_Physics.GetRotation();
//
//                // translate the rotation to degrees
//                float degrees = rotation * RAD2DEG;
//                degrees = fmod(degrees, 360);
//
//                DrawCircleSector(position,10,0,degrees,(5*((int)degrees)%180),DARKGREEN);
//            }
//
//            if (Debug::HasFlags(Debug::DRAW_VERTICES)){
//                // Get the position of the object
//                Vector2 position = m_Physics.GetPosition();
//
//                // Get the rotation of the object
//                float rotation = m_Physics.GetRotation();
//
//                // Get the vertices of the object
//                auto vertices = m_Physics.GetMesh()->GetVertices();
//
//                for (auto vertex : vertices){
//                    Vector2 vertex_world = Vector2Add(Vector2Rotate(vertex,rotation) , position);
//                    DrawCircleV(vertex_world, 5, DARKBLUE);
//                }
//
//            }
//
//            // get mesh and call DrawDebug
//            m_Physics.GetMesh()->DrawDebug(m_Physics.GetPosition(), m_Physics.GetRotation());

    }
}