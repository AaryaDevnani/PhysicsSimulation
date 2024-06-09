#include "PrimeEngine/APIAbstraction/APIAbstractionDefines.h"

#include "PrimeEngine/Lua/LuaEnvironment.h"
#include "../ClientGameObjectManagerAddon.h"
#include "../CharacterControlContext.h"
#include "SoldierNPCMovementSM.h"
#include "SoldierNPCAnimationSM.h"
#include "SoldierNPC.h"

#include "PrimeEngine/Physics/PhysicsManager.h"
#include "PrimeEngine/Physics/PhysicsComponent.h"
#include "PrimeEngine/Physics/Shape.h"

using namespace PE::Components;
using namespace PE::Events;
using namespace CharacterControl::Events;

namespace CharacterControl{

// Events sent by behavior state machine (or other high level state machines)
// these are events that specify where a soldier should move
namespace Events{

PE_IMPLEMENT_CLASS1(SoldierNPCMovementSM_Event_MOVE_TO, Event);

SoldierNPCMovementSM_Event_MOVE_TO::SoldierNPCMovementSM_Event_MOVE_TO(Vector3 targetPos /* = Vector3 */)
: m_targetPosition(targetPos)
{ }


//PE_IMPLEMENT_CLASS1(SoldierNPCMovementSM_Event_AIM_AT_TARGET, Event);

//SoldierNPCMovementSM_Event_AIM_AT_TARGET::SoldierNPCMovementSM_Event_AIM_AT_TARGET(Vector3 targetPos /* = Vector3 */)
//	: m_targetPosition(targetPos)
//{ }
PE_IMPLEMENT_CLASS1(SoldierNPCMovementSM_Event_STOP, Event);

PE_IMPLEMENT_CLASS1(SoldierNPCMovementSM_Event_TARGET_REACHED, Event);
}

namespace Components{

PE_IMPLEMENT_CLASS1(SoldierNPCMovementSM, Component);


SoldierNPCMovementSM::SoldierNPCMovementSM(PE::GameContext &context, PE::MemoryArena arena, PE::Handle hMyself) 
: Component(context, arena, hMyself)
, m_state(STANDING)
{}

SceneNode *SoldierNPCMovementSM::getParentsSceneNode()
{
	PE::Handle hParent = getFirstParentByType<Component>();
	if (hParent.isValid())
	{
		// see if parent has scene node component
		return hParent.getObject<Component>()->getFirstComponent<SceneNode>();
		
	}
	return NULL;
}

void SoldierNPCMovementSM::addDefaultComponents()
{
	Component::addDefaultComponents();

	PE_REGISTER_EVENT_HANDLER(SoldierNPCMovementSM_Event_MOVE_TO, SoldierNPCMovementSM::do_SoldierNPCMovementSM_Event_MOVE_TO);
	//PE_REGISTER_EVENT_HANDLER(SoldierNPCMovementSM_Event_AIM_AT_TARGET, SoldierNPCMovementSM::do_SoldierNPCMovementSM_Event_AIM_AT_TARGET);
	PE_REGISTER_EVENT_HANDLER(SoldierNPCMovementSM_Event_STOP, SoldierNPCMovementSM::do_SoldierNPCMovementSM_Event_STOP);
	PE_REGISTER_EVENT_HANDLER(Event_UPDATE, SoldierNPCMovementSM::do_UPDATE);
}

void SoldierNPCMovementSM::do_SoldierNPCMovementSM_Event_MOVE_TO(PE::Events::Event *pEvt)
{
	SoldierNPCMovementSM_Event_MOVE_TO *pRealEvt = (SoldierNPCMovementSM_Event_MOVE_TO *)(pEvt);
	
	// change state of this state machine
	m_state = WALKING_TO_TARGET;
	m_targetPostion = pRealEvt->m_targetPosition;

	// make sure the animations are playing
	
	PE::Handle h("SoldierNPCAnimSM_Event_WALK", sizeof(SoldierNPCAnimSM_Event_WALK));
	Events::SoldierNPCAnimSM_Event_WALK *pOutEvt = new(h) SoldierNPCAnimSM_Event_WALK();
	
	SoldierNPC *pSol = getFirstParentByTypePtr<SoldierNPC>();
	pSol->getFirstComponent<PE::Components::SceneNode>()->handleEvent(pOutEvt);

	// release memory now that event is processed
	h.release();
}

void SoldierNPCMovementSM::do_SoldierNPCMovementSM_Event_STOP(PE::Events::Event *pEvt)
{
	Events::SoldierNPCAnimSM_Event_STOP Evt;

	SoldierNPC *pSol = getFirstParentByTypePtr<SoldierNPC>();
	pSol->getFirstComponent<PE::Components::SceneNode>()->handleEvent(&Evt);
}

//void SoldierNPCMovementSM::do_SoldierNPCMovementSM_Event_AIM_AT_TARGET()

void SoldierNPCMovementSM::do_UPDATE(PE::Events::Event *pEvt)
{
	
	if (m_state == WALKING_TO_TARGET)
	{
		// see if parent has scene node component
		SceneNode *pSN = getParentsSceneNode();
		if (pSN)
		{
			Vector3 curPos = pSN->m_base.getPos();
			float dsqr = (m_targetPostion - curPos).lengthSqr();

			bool reached = true;
			if (dsqr > 0.01f)
			{
				PhysicsComponent* pcSN = pSN->pcSN;
				
				/*pcSN->m_shape.*/
				// not at the spot yet
				Event_UPDATE *pRealEvt = (Event_UPDATE *)(pEvt);
				static float speed = 1.4f;
				float allowedDisp = speed * pRealEvt->m_frameTime;
				Vector3 offset = pcSN->checkCollisions();
				
				Vector3 dir= (m_targetPostion - curPos);
				if(offset.m_x != 0 || offset.m_y != 0 || offset.m_z != 0)
				{
					//Vector3 cross = offset.crossProduct(pSN->m_base.getV());

					/*Vector3 newDir = (dir.dotProduct(offset)) * offset;
					dir = newDir;*/
					dir = -pSN->m_base.getU();

				}


				
				dir.normalize();
				float dist = sqrt(dsqr);
				if (dist > allowedDisp)
				{
					dist = allowedDisp; // can move up to allowedDisp
					reached = false; // not reaching destination yet
				}
				
				if (pcSN->checkFloor()) {
					// instantaneous turn
					//pSN->m_base.turnInDirection(dir, 3.1415f);
					pcSN->m_Center = curPos + dir * dist + Vector3(0, 1.0f, 0);
					pSN->m_base.setPos(curPos + dir * dist);
				}
				else {
					pcSN->m_Center = curPos + Vector3(0, -1.0f, 0) * 2 + Vector3(0, 1.0f, 0);
					pSN->m_base.setPos(curPos + Vector3(0,-1.0f,0) * 2);
				}
				
				
			}

			if (reached)
			{

				m_state = STANDING;

				{
					PE::Handle h("SoldierNPCMovementSM_Event_TARGET_REACHED", sizeof(SoldierNPCMovementSM_Event_TARGET_REACHED));
					Events::SoldierNPCMovementSM_Event_TARGET_REACHED* pOutEvt = new(h) SoldierNPCMovementSM_Event_TARGET_REACHED();

					PE::Handle hParent = getFirstParentByType<Component>();
					if (hParent.isValid())
					{
						hParent.getObject<Component>()->handleEvent(pOutEvt);
					}

					// release memory now that event is processed
					h.release();
				}

				if (m_state == STANDING)
				{
					m_state = STAND_SHOOT;
					
					// no one has modified our state based on TARGET_REACHED callback
					// this means we are not going anywhere right now
					// so can send event to animation state machine to stop
					
					{
						Events::SoldierNPCAnimSM_Event_SHOOT evt;
						SoldierNPC *pSol = getFirstParentByTypePtr<SoldierNPC>();

						
						//tSol = pSol;
						pSol->getFirstComponent<PE::Components::SceneNode>()->handleEvent(&evt);
												
						
					}
					
					

				}


						
				
			}
		}
	}
}

}}




