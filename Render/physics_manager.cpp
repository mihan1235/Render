#include <physics_manager.hpp>
#include <cstdio>
#include <render.hpp>
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>


namespace {
	PhysicsManager physics_manager;
}

PhysicsManager::PhysicsManager(){
	///collision configuration contains default setup for memory, 
	///collision setup. Advanced users can create their own 
	///configuration.
	collisionConfiguration = new btDefaultCollisionConfiguration();
	///use the default collision dispatcher. For parallel processing
	///you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher =new btCollisionDispatcher(collisionConfiguration);
	btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);
	///btDbvtBroadphase is a good general purpose broadphase. You can 
	///also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();
	///the default constraint solver. For parallel processing you can 
	///use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,
					overlappingPairCache,solver,collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0,-10,0));
	/* create the debug drawer
	m_pDebugDrawer = new BtDebugDrawer();
	 set the initial debug level to 0
	m_pDebugDrawer->setDebugMode(0);
	 add the debug drawer to the world
	m_pDebugDrawer->ToggleDebugFlag(btIDebugDraw::DBG_DrawWireframe);
	dynamicsWorld->setDebugDrawer(m_pDebugDrawer);*/
	
};

void PhysicsManager::set_debug_drawer(BtDebugDrawer* DebugDrawer) {
	// create the debug drawer
	m_pDebugDrawer = DebugDrawer;
	// set the initial debug level to 0
	m_pDebugDrawer->setDebugMode(0);
	// add the debug drawer to the world
	dynamicsWorld->setDebugDrawer(m_pDebugDrawer);
}

void PhysicsManager::draw_debug_drawer() {
	if (m_pDebugDrawer != nullptr) {
		dynamicsWorld->debugDrawWorld();
		m_pDebugDrawer->draw();
	}
}

void PhysicsManager::start_simulation_step(){
	//dynamicsWorld->stepSimulation(get_delta_time()/3,10);
	dynamicsWorld->stepSimulation(get_delta_time()/6, 10);
	
	
	//for (int j=dynamicsWorld->getNumCollisionObjects()-1; j>=0 ;j--)
		//{
			//btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
			//btRigidBody* body = btRigidBody::upcast(obj);
			//btTransform trans;
			//if (body && body->getMotionState())
			//{
				//body->getMotionState()->getWorldTransform(trans);

			//} else
			//{
				//trans = obj->getWorldTransform();
			//}
			//printf("world pos object %d = %f,%f,%f\n",j,float(trans.getOrigin().getX()),float(trans.getOrigin().getY()),float(trans.getOrigin().getZ()));
		//}
}

void PhysicsManager::add_rigid_body(Object* physics_obj){
	btCollisionShape* groundShape = physics_obj->get_shape();
	collisionShapes.push_back(groundShape);
	btTransform groundTransform = physics_obj->get_default_btTransform();
	
	{
		btScalar mass(physics_obj->get_mass());
		printf("mass: [%lf]\n", physics_obj->get_mass());
		//rigidbody is dynamic if and only if mass is non zero, 
		//otherwise static
		bool isDynamic = (mass != 0.f);
		btVector3 localInertia(0,0,0);
		if (isDynamic){
			groundShape->calculateLocalInertia(mass,localInertia);
		}
		//using motionstate is optional, it provides interpolation 
		//capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = 
							new btDefaultMotionState(groundTransform);
		//myMotionState->setWorldTransform(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo 
					rbInfo(mass,myMotionState,groundShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);
		//body->setWorldTransform(groundTransform);
		//body->setFriction(btScalar(0.9));
		physics_obj->set_rigid_body(body);
		//add the body to the dynamics world
		dynamicsWorld->addRigidBody(body);
	}
}

PhysicsManager::~PhysicsManager(){
	int i;
	//remove the rigidbodies from the dynamics world and delete them
	for (i=dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject( obj );
		delete obj;
	}
	//delete collision shapes
	for (int j=0;j<collisionShapes.size();j++)
	{
		btCollisionShape* shape = collisionShapes[j];
		collisionShapes[j] = 0;
		//delete shape;
	}
	//delete dynamics world
	delete dynamicsWorld;
	//delete solver
	delete solver;
	//delete broadphase
	delete overlappingPairCache;
	//delete dispatcher
	delete dispatcher;
	delete collisionConfiguration;
};


void start_simulation_step() {
	physics_manager.start_simulation_step();
}

void add_rigid_body(Object* physics_obj) {
	physics_manager.add_rigid_body(physics_obj);
}

BtDebugDrawer* PhysicsManager::get_debug_drawer() {
	return m_pDebugDrawer;
}

BtDebugDrawer* get_debug_drawer() {
	return physics_manager.get_debug_drawer();
}

void set_debug_drawer(BtDebugDrawer* obj) {
	physics_manager.set_debug_drawer(obj);
}

void draw_debug_drawer() {
	physics_manager.draw_debug_drawer();
}

