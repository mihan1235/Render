#pragma once
#include <object/object.hpp>

namespace kr{
	class Triangle: public Render{
		int num_vertices;
	public:
		Triangle(ShaderProgram* shader_program);
		~Triangle();
		void draw(ShaderProgram* shader_program);
	private:
		void set_shaders_parameters(ShaderProgram* shader_program);
	protected:
		
	};
}


