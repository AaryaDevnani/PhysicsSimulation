#ifndef __PYENGINE_2_0_PHYSICSCOMPONENT_H__
#define __PYENGINE_2_0_PHYSICSCOMPONENT_H__

// API Abstraction
#include "PrimeEngine/APIAbstraction/APIAbstractionDefines.h"

// Outer-Engine includes
#include <assert.h>

// Inter-Engine includes
#include "PrimeEngine/MemoryManagement/Handle.h"
#include "PrimeEngine/PrimitiveTypes/PrimitiveTypes.h"
#include "PrimeEngine/Events/Component.h"
#include "PrimeEngine/Utils/Array/Array.h"
#include "Shape.h"
#include "PrimeEngine/Math/Vector3.h"
//#include "PrimeEngine/Physics/PhysicsManager.h"
//#include "PrimeEngine/Scene/SceneNode.h"

//#define USE_DRAW_COMPONENT

namespace PE {
	namespace Components {
		class SceneNode;
		class PhysicsManager;
		struct PhysicsComponent
		{
			//PE_DECLARE_CLASS(PhysicsComponent);

			// Constructor -------------------------------------------------------------
			PhysicsComponent(Shape::Type shape, SceneNode* pSN, float radius, Vector3 center);

			PhysicsComponent(Shape::Type shape, SceneNode* pSN, Vector3 AABB[]);



			virtual ~PhysicsComponent() {}

			Vector3 PhysicsComponent::checkCollisions();
			bool PhysicsComponent::checkFloor();

		public:
			Shape::Type m_shape;
			Vector3 m_AABBCoords[8];
			Vector3 m_Center;
			float m_radius;

			SceneNode* m_pSN;

			// Component ---------------------------------------------------------------

			//virtual void addDefaultComponents();

			// Individual events -------------------------------------------------------

			//PhysicsComponent(Shape shape);

		}; // class PhysicsComponent

	}; // namespace Components
}; // namespace PE

#endif // PHYSICSCOMPONENT_H
