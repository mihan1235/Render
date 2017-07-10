#include <physics_manager.hpp>
#include <cstdio>


using namespace kr;

PhysicsManager::PhysicsManager(){
	///collision configuration contains default setup for memory, 
	///collision setup. Advanced users can create their own 
	///configuration.
	collisionConfiguration = new btDefaultCollisionConfiguration();
	///use the default collision dispatcher. For parallel processing
	///you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher =new btCollisionDispatcher(collisionConfiguration);
	///btDbvtBroadphase is a good general purpose broadphase. You can 
	///also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();
	///the default constraint solver. For parallel processing you can 
	///use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,
					overlappingPairCache,solver,collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0,-10,0));
};

void PhysicsManager::start_simulation_step(){
	//dynamicsWorld->stepSimulation(Core::get_delta_time()/3,10);
	dynamicsWorld->stepSimulation(Core::get_delta_time(), 10);
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

void PhysicsManager::add_rigid_body(PhysicsObject* physics_obj){
	btCollisionShape* groundShape = physics_obj->get_shape();
	collisionShapes.push_back(groundShape);
	btTransform groundTransform;
	groundTransform.setIdentity();
	glm::vec3 pos=physics_obj->get_default_position();
	groundTransform.setOrigin(btVector3(pos.x,pos.y,pos.z));
	{
		btScalar mass(physics_obj->get_mass());
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
		btRigidBody::btRigidBodyConstructionInfo 
					rbInfo(mass,myMotionState,groundShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);
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
		delete shape;
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
