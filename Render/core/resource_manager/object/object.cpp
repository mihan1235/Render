#include <object.hpp>

namespace kr {
	Object::Object(btCollisionShape* shape, float mass, ShaderProgram* shader_program
		, glm::vec3 position, const char* texture_name, glm::mat4 scale
		, glm::mat4 rotate) :PhysicsObject(shape, mass, position, scale, rotate),
										   Render(shader_program)
	{
		this->texture_name = texture_name;
	}
}