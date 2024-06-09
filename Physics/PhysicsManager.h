#ifndef  __PYENGINE_2_0_PHYSICSMANAGER_H__
#define  __PYENGINE_2_0_PHYSICSMANAGER_H__

#include <vector>
#include "PhysicsComponent.h"

namespace PE {
    namespace Components {

        class PhysicsManager {
        public:

            static PhysicsManager* getInstance();

            // Function to add a PhysicsComponent
            void addPhysicsComponent(PhysicsComponent* physicsComponent);

            // Function to get all components
            std::vector<PhysicsComponent*> getComponents();

        private:

            PhysicsManager() {}

            static PhysicsManager* pPhyMgr;		// singleton instance

            std::vector<PhysicsComponent*> m_physicsComponents;
        };

    } // namespace Components
} // namespace PE
#endif // PHYSICSMANAGER_H
