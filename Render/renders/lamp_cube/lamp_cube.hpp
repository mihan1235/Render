#pragma once
#include <object/object.hpp>

namespace kr{
	class LampCube: public Render{
		glm::vec3 lightPos;
	public:
		LampCube(ShaderProgram* shader_program);
		~LampCube();
		void draw(ShaderProgram* shader_program);
	private:
		void set_shaders_parameters(ShaderProgram* shader_program);
	protected:
		
	};
}
