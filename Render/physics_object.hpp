#pragma once
#include "btBulletDynamicsCommon.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>


class IPhysicsObject{
public:
	IPhysicsObject(glm::vec3 position,float mass);
	virtual ~IPhysicsObject();
	virtual btCollisionShape* get_shape()=0;
	btRigidBody* get_rigid_body();
	float get_mass();
	void set_mass(float mass);
	virtual glm::vec3 get_default_position();
	virtual btTransform get_default_btTransform();
	void set_rigid_body(btRigidBody* body);
	glm::mat4 get_model();
private:
	IPhysicsObject(const IPhysicsObject&);
	IPhysicsObject& operator=(const IPhysicsObject&) {};
protected:
	//static btCollisionShape* shape;
	btRigidBody* body=nullptr;
	float mass;
	glm::vec3 default_position;
	glm::vec3 position();
	glm::quat orientation();
	virtual void make_btCollisionShape() = 0;
	
};

btCollisionShape* get_btConvexHullShape(std::vector<btVector3>& points);
btCollisionShape* get_btConvexTriangleMeshShape(std::vector<btVector3>& points, std::vector<int>& indices);
btCollisionShape* get_btBvhTriangleMeshShape(std::vector<btVector3>& points, std::vector<int>& indices);
btCollisionShape* get_btGImpactMeshShape(std::vector<btVector3>& points, std::vector<int>& indices);


