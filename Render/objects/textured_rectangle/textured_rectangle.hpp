#pragma once
#include <object.hpp>

namespace kr{
	class TexturedRectangle: public Object{
		int num_vertices;
	public:
		TexturedRectangle(btCollisionShape* shape, float mass, ShaderProgram* shader_program
			, glm::vec3 position, const char* texture_name, glm::mat4 scale = glm::mat4()
			, glm::mat4 rotate = glm::mat4());
		~TexturedRectangle();
		void draw(ShaderProgram* shader_program);
	private:
		void set_shaders_parameters(ShaderProgram* shader_program);
	protected:
		
	};
}
