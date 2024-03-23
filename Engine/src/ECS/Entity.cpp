//
// Created by Bekir Gulestan on 3/23/24.
//

#include "Entity.h"
#include "Engine.h"

#include <utility>

namespace RayEngine {

    Entity::Entity(){
        m_Scene = Engine::GetScene();
        m_Id = m_Scene->CreateEntity();
        m_Scene->RecordEntity(this);
    }


    Entity::Entity(EntityID id,  std::shared_ptr<Scene> scene) : m_Id(id), m_Scene(std::move(scene)) {
    }





}
