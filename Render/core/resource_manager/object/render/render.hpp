#pragma once
#include <GL/glew.h>
#include <shader_program.hpp>
#include <vector>
#include <texture_operations.hpp>
#include <file_operations.hpp>

namespace kr{
	class Render{
	public:
		Render(ShaderProgram* shader_program){
			this->shader_program = shader_program;
		};
		virtual ~Render();
		virtual void draw(ShaderProgram* shader_program=nullptr)=0;
	private:
		Render(const Render&);
		Render& operator=(const Render&) {};
	protected:
		ShaderProgram* shader_program;
		GLuint VBO, VAO;
		GLuint EBO;
		virtual void set_shaders_parameters(ShaderProgram* shader_program = nullptr)=0;
	};

}
