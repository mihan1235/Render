#pragma once
#include <GL/glew.h>
#include <string>
#include <object/shader_program/shader_type.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace kr{
	class ShaderProgram{
	public:
		ShaderProgram(const GLchar* vertex_source,const GLchar* fragment_source,
			const GLchar* geometry_source=nullptr);
		~ShaderProgram();
		void use();
		int set_uniform_float (const GLchar *name, GLfloat value);
		int set_uniform_integer (const GLchar *name, GLint value);
		int set_uniform_vector2f (const GLchar *name, GLfloat x, GLfloat y);
		int set_uniform_vector2f (const GLchar *name, const glm::vec2 &value);
		int set_uniform_vector3f (const GLchar *name, GLfloat x, GLfloat y, 
								  GLfloat z);
		int set_uniform_vector3f (const GLchar *name, const glm::vec3 &value);
		int set_uniform_vector4f (const GLchar *name, GLfloat x, GLfloat y,
								  GLfloat z, GLfloat w);
		int set_uniform_vector4f (const GLchar *name, const glm::vec4 &value);
		int set_uniform_matrix4 (const GLchar *name, const glm::mat4 &matrix);
		GLuint get_id();
	private:
		int compile(ShaderType);
		void attach(ShaderType);
		int check_link_success();
		int check_compile_success(ShaderType);
		GLuint create_shader(ShaderType);
		const GLchar* vertex_source;
		const GLchar* fragment_source;
		const GLchar* geometry_source;
		void delete_shader(ShaderType);
	protected:
		GLboolean is_used=false;
		GLuint vertex_id;
		GLuint fragment_id;
		GLuint geometry_id;
		GLuint program_id;
	};
}
