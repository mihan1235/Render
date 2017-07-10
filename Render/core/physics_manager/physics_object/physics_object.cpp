#include <physics_object.hpp>

using namespace kr;

PhysicsObject::PhysicsObject(btCollisionShape* shape,float mass,
							 glm::vec3 position,
							 glm::mat4 scale,glm::mat4 rotate)
{
	this->shape=shape;
	this->mass=mass;
	this->scale=scale;
	this->rotate=rotate;
	default_position=position;
};

//void PhysicsObject::draw(){
//    obj->draw(get_model()*scale*rotate);    
//}

glm::mat4 PhysicsObject::get_model() {
    return glm::translate(glm::mat4(), position()) * glm::mat4_cast(orientation());
}

glm::vec3 PhysicsObject::position() {
    btTransform transform;
    body->getMotionState()->getWorldTransform(transform);
    return {transform.getOrigin().getX(), transform.getOrigin().getY(), transform.getOrigin().getZ()};
}

glm::quat PhysicsObject::orientation() {
    btTransform transform;
    body->getMotionState()->getWorldTransform(transform);
    return glm::angleAxis(transform.getRotation().getAngle(),
						 glm::normalize(glm::vec3(
                         transform.getRotation().getAxis().getX(),
                         transform.getRotation().getAxis().getY(),
                         transform.getRotation().getAxis().getZ())));
}

btCollisionShape* PhysicsObject::get_shape() { 
	return shape;
}

btRigidBody* PhysicsObject::get_rigid_body() { 
	return body;
}

void PhysicsObject::set_rigid_body(btRigidBody* body) { 
	this->body=body;
}

float PhysicsObject::get_mass(){
	return mass;
}

void PhysicsObject::set_mass(float mass){
	this->mass=mass;
}

PhysicsObject::~PhysicsObject(){
	
};

glm::vec3 PhysicsObject::get_default_position(){
	return default_position;
}
