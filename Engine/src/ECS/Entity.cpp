//
// Created by Bekir Gulestan on 3/23/24.
//

#include "Entity.h"
#include "Engine.h"

#include <utility>

namespace RayEngine {

    Entity::Entity(){
        //
        std::cout << "Entity created..." << std::endl;

        m_Scene = Engine::GetScene();
        m_Id = m_Scene->CreateEntity();

        // Record the entity
        m_Scene->RecordEntity(this);
    }
}
