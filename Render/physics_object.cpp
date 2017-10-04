#include <physics_object.hpp>



IPhysicsObject::IPhysicsObject(glm::vec3 position,float mass){
	this->mass=mass;
	this->default_position = position;
};

glm::mat4 IPhysicsObject::get_model() {
    return glm::translate(glm::mat4(), position()) * glm::mat4_cast(orientation());
}

glm::vec3 IPhysicsObject::position() {
    btTransform transform;
    body->getMotionState()->getWorldTransform(transform);
    return {transform.getOrigin().getX(), transform.getOrigin().getY(), transform.getOrigin().getZ()};
}

glm::quat IPhysicsObject::orientation() {
    btTransform transform;
    body->getMotionState()->getWorldTransform(transform);
    return glm::angleAxis(transform.getRotation().getAngle(),
						 glm::normalize(glm::vec3(
                         transform.getRotation().getAxis().getX(),
                         transform.getRotation().getAxis().getY(),
                         transform.getRotation().getAxis().getZ())));
}

btCollisionShape* IPhysicsObject::get_shape() { 
	return shape;
}

btRigidBody* IPhysicsObject::get_rigid_body() { 
	return body;
}

void IPhysicsObject::set_rigid_body(btRigidBody* body) { 
	this->body=body;
}

float IPhysicsObject::get_mass(){
	return mass;
}

void IPhysicsObject::set_mass(float mass){
	this->mass=mass;
}

IPhysicsObject::~IPhysicsObject(){
	
};

glm::vec3 IPhysicsObject::get_default_position(){
	return default_position;
}
