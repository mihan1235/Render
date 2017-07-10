#pragma once
#include <object/object.hpp>

namespace kr{
	class Cube: public Object{
		int num_vertices;
	public:
		Cube(btCollisionShape* shape, float mass,  ShaderProgram* shader_program
			, glm::vec3 position, const char* texture_name, glm::mat4 scale = glm::mat4()
			, glm::mat4 rotate = glm::mat4());
		~Cube();
		void draw(ShaderProgram* shader_program);
	private:
		void set_shaders_parameters(ShaderProgram* shader_program);
	protected:
		
	};
}
