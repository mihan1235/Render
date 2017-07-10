#pragma once
#include "btBulletDynamicsCommon.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace kr{
	class PhysicsObject{
	public:
		PhysicsObject(btCollisionShape* shape=nullptr,float mass=0.0f
					 , glm::vec3 position = glm::vec3(), glm::mat4 scale=glm::mat4()
					 , glm::mat4 rotate=glm::mat4());
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
		glm::mat4 scale;
		glm::mat4 rotate;
	};
}
