
#include "PhysicsManager.h"
#include <vector>
#include "PhysicsComponent.h"

namespace PE {
    namespace Components {

        PhysicsManager* PhysicsManager::pPhyMgr = NULL;

        //PhysicsManager::PhysicsManager()
        //{
        //    // do init stuff
        //}

        PhysicsManager* PhysicsManager::getInstance()
        {
            if (pPhyMgr == NULL) {
                pPhyMgr = new PhysicsManager();
            }
            return pPhyMgr;
        }

        void PhysicsManager::addPhysicsComponent(PhysicsComponent* physicsComponent) {
            m_physicsComponents.push_back(physicsComponent);
            PEINFO("PhysicsManager: Component added successfuly.");
        }

        std::vector<PhysicsComponent*> PhysicsManager::getComponents() {
            return m_physicsComponents;
        }

      
    } // namespace Components
} // namespace PE
