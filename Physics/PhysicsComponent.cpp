
#include "PhysicsComponent.h"
#include "PrimeEngine/Lua/LuaEnvironment.h"
#include "Shape.h"
#include "PrimeEngine/Events/StandardEvents.h"
#include "PrimeEngine/Scene/SceneNode.h"
#include "PrimeEngine//Physics/PhysicsManager.h"

namespace PE {
	namespace Components {

		PhysicsComponent::PhysicsComponent(Shape::Type shape, SceneNode* pSN, Vector3 AABB[]) : m_shape(shape), m_pSN(pSN)
		{
			if (shape == Shape::Type::BOX ) {
				for (int i = 0; i < 8; i++) {
					m_AABBCoords[i] = AABB[i];
				}
				PEINFO("PhysicsComponent: PhysicsComponent BOX constructed.\n");
			}
			else {
				for (int i = 0; i < 8; i++) {
					m_AABBCoords[i] = AABB[i];
				}
				PEINFO("PhysicsComponent: PhysicsComponent PLANE constructed.\n");
			}
			
			
		}

		PhysicsComponent::PhysicsComponent(Shape::Type shape, SceneNode* pSN,  float radius, Vector3 Center) : m_shape(shape), m_pSN(pSN), m_Center(Center), m_radius(radius)
		{
			// Initialize physics component with the provided shape
			PEINFO("PhysicsComponent: PhysicsComponent SPHERE constructed.\n");
		}

		Vector3 PhysicsComponent::checkCollisions(){
			Vector3 localSphereCenter = m_pSN->m_worldTransform.inverse() * m_Center;
			std::vector<PhysicsComponent*> allComponents = PhysicsManager::getInstance()->getComponents();
			for (const PhysicsComponent* i : allComponents) {
				if (i->m_shape == Shape::Type::BOX) {
					//detect collisions here
					float x = max(i->m_AABBCoords[0].m_x, min(localSphereCenter.m_x, i->m_AABBCoords[5].m_x));
					float y = max(i->m_AABBCoords[0].m_y, min(localSphereCenter.m_y, i->m_AABBCoords[5].m_y));
					float z = max(i->m_AABBCoords[0].m_z, min(localSphereCenter.m_z, i->m_AABBCoords[5].m_z));
					Vector3 closestPoint(x, y, z);
					Vector3 offset =  (m_Center - closestPoint);
					float l = offset.length();
					if (offset.length() <= m_radius) {
						//PEINFO("COLLISION");
						return offset;
					}
					else {
						//PEINFO("NO COLLISION");
					//	//return Vector3(0, 0, 0);
					}
				}
			}
			return Vector3(0, 0, 0);
			
		}

		bool PhysicsComponent::checkFloor() {
			Vector3 localSphereCenter =/* m_pSN->m_worldTransform.inverse() **/ m_Center;
			std::vector<PhysicsComponent*> allComponents = PhysicsManager::getInstance()->getComponents();
			bool onFloor = true;
			for (const PhysicsComponent* i : allComponents) {
				if (i->m_shape == Shape::Type::PLANE) {
					float x = max(i->m_AABBCoords[0].m_x, min(localSphereCenter.m_x, i->m_AABBCoords[5].m_x));
					float y = max(i->m_AABBCoords[0].m_y, min(localSphereCenter.m_y, i->m_AABBCoords[5].m_y));
					float z = max(i->m_AABBCoords[0].m_z, min(localSphereCenter.m_z, i->m_AABBCoords[5].m_z));
					Vector3 closestPoint(x, y, z);
					Vector3 offset = localSphereCenter - closestPoint;
					onFloor = offset.length()+1 <= m_radius;
				}
			}
			return onFloor;
		}
	}; // namespace Components
}; // namespace PE
