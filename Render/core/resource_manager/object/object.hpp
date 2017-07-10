#pragma once
#include <render.hpp>
#include <physics_object.hpp>

namespace kr {
	class Object : public Render, public PhysicsObject {
		
	public:
		Object(btCollisionShape* shape, float mass, ShaderProgram* shader_program
			, glm::vec3 position, const char* texture_name=nullptr, glm::mat4 scale = glm::mat4()
			, glm::mat4 rotate = glm::mat4());
		virtual ~Object() {};
	private:
		Object(const Object&);
		Object& operator=(const Object&) {};
	protected:
		const char* texture_name;
	};
}
