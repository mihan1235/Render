#pragma once
#include "btBulletDynamicsCommon.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>


class IPhysicsObject{
public:
	IPhysicsObject(glm::vec3 position,float mass=0.0f);
	~IPhysicsObject();
	btCollisionShape* get_shape();
	btRigidBody* get_rigid_body();
	float get_mass();
	void set_mass(float mass);
	glm::vec3 get_default_position();
	void set_rigid_body(btRigidBody* body);
	glm::mat4 get_model();
private:
	IPhysicsObject(const IPhysicsObject&);
	IPhysicsObject& operator=(const IPhysicsObject&) {};
protected:
	btCollisionShape* shape=nullptr;
	btRigidBody* body=nullptr;
	float mass;
	glm::vec3 default_position;
	glm::vec3 position();
	glm::quat orientation();
};

