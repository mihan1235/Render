#pragma once
#include "btBulletDynamicsCommon.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <object.hpp>
#include <BtDebugDrawer.hpp>


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
	BtDebugDrawer* m_pDebugDrawer;
public:
	PhysicsManager();
	void start_simulation_step();
	void add_rigid_body(Object* physics_obj);
	BtDebugDrawer* get_debug_drawer();
	void draw_debug_drawer();
	void set_debug_drawer(BtDebugDrawer* m_pDebugDrawer);
	//////////////////////////////////////////////
	~PhysicsManager();
private:
	PhysicsManager(const PhysicsManager&);
	PhysicsManager& operator=(const PhysicsManager&) {};
protected:
	
};


void start_simulation_step();
void add_rigid_body(Object* physics_obj);
BtDebugDrawer* get_debug_drawer();
void set_debug_drawer(BtDebugDrawer* obj);
void draw_debug_drawer();


