#pragma once
#include "btBulletDynamicsCommon.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <physics_object.hpp>
#include <object.hpp>

namespace kr{
	class PhysicsManager{
		btDefaultCollisionConfiguration* collisionConfiguration;
		btCollisionDispatcher* dispatcher;
		btBroadphaseInterface* overlappingPairCache;
		btSequentialImpulseConstraintSolver* solver;
		btDiscreteDynamicsWorld* dynamicsWorld;
		//keep track of the shapes, we release memory at exit.
		//make sure to re-use collision shapes among rigid bodies 
		//whenever possible!
		btAlignedObjectArray<btCollisionShape*> collisionShapes;
	public:
		PhysicsManager();
		void start_simulation_step();
		void add_rigid_body(PhysicsObject* physics_obj);
		//////////////////////////////////////////////
		~PhysicsManager();
	private:
		PhysicsManager(const PhysicsManager&);
		PhysicsManager& operator=(const PhysicsManager&) {};
	protected:
		
	};
}


