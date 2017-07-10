#pragma once
#include "btBulletDynamicsCommon.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <object.hpp>


class PhysicsObject: public Object{
public:
	PhysicsObject(glm::vec3 position, btCollisionShape* shape=nullptr,float mass=0.0f);
	~PhysicsObject();
	btCollisionShape* get_shape();
	btRigidBody* get_rigid_body();
	float get_mass();
	void set_mass(float mass);
	glm::vec3 get_default_position();
	void set_rigid_body(btRigidBody* body);
	glm::mat4 get_model();
private:
	PhysicsObject(const PhysicsObject&);
	PhysicsObject& operator=(const PhysicsObject&) {};
protected:
	btCollisionShape* shape;
	btRigidBody* body;
	float mass;
	glm::vec3 default_position;
	glm::vec3 position();
	glm::quat orientation();
};

