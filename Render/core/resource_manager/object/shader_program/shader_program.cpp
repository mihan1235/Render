#include <shader_program.hpp>
#include <cstdio>

using namespace kr;

GLuint ShaderProgram::create_shader(ShaderType type){
	switch (type){
		case vertex:{
			return glCreateShader(GL_VERTEX_SHADER);
			break;
		}
		case fragment:{
			return glCreateShader(GL_FRAGMENT_SHADER);
			break;
		}
		case geometry:{
			return glCreateShader(GL_GEOMETRY_SHADER);
			break;
		}
		default:{
			printf("Create::unknown shader type!!\n");
			break;
		}
	}
	return 1;
}

ShaderProgram::ShaderProgram(const GLchar* vertex_source,const GLchar* fragment_source,
							const GLchar* geometry_source){
	this->vertex_source=vertex_source;
	this->fragment_source=fragment_source;
	this->geometry_source=geometry_source;
	vertex_id=create_shader(vertex);
	fragment_id=create_shader(fragment);
	if (geometry_source!=nullptr){
		geometry_id=create_shader(geometry);
	}
	compile(vertex);
	compile(fragment);
	if (geometry_source!=nullptr){
		compile(geometry);
	}
	program_id=glCreateProgram();
	attach(vertex);
	attach(fragment);
	if (geometry_source!=nullptr){
		attach(geometry);
	}
	glLinkProgram(program_id);
	check_link_success();
	delete_shader(vertex);
	delete_shader(fragment);
	if (geometry_source!=nullptr){
		delete_shader(geometry);
	}
}

void ShaderProgram::delete_shader(ShaderType type){
	switch (type){
		case vertex: {
			glDeleteShader(vertex_id);
			break;
		}
		case fragment: {
			glDeleteShader(fragment_id);
			break;
		}
		case geometry: {
			glDeleteShader(geometry_id);
			break;
		}
		default:{
			printf("Deleting::unknown shader type!!\n");
			break;
		}
	}
}

void ShaderProgram::use(){
	is_used=true;
	 glUseProgram(program_id);
}

int ShaderProgram::compile(ShaderType type){
	switch (type){
		case vertex: {
			glShaderSource(vertex_id, 1, &vertex_source, NULL);
			glCompileShader(vertex_id);
			return check_compile_success(vertex);
			break;
		}
		case fragment: {
			glShaderSource(fragment_id, 1, &fragment_source, NULL);
			glCompileShader(fragment_id);
			return check_compile_success(fragment);
			break;
		}
		case geometry: {
			glShaderSource(geometry_id, 1, &geometry_source, NULL);
			glCompileShader(geometry_id);
			return check_compile_success(geometry);
			break;
		}
		default:{
			printf("Compile::unknown shader type!!\n");
			break;
		}
	}
	return 1;
}

void ShaderProgram::attach(ShaderType type){
	switch (type){
		case vertex: {
			glAttachShader(program_id, vertex_id);
			break;
		}
		case fragment: {
			glAttachShader(program_id, fragment_id);
			break;
		}
		case geometry: {
			glAttachShader(program_id, geometry_id);
			break;
		}
		default:{
			printf("Attach::unknown shader type!!\n");
			break;
		}
	}
}

int ShaderProgram::check_link_success(){
	GLint success;
    GLchar info_log[1024];
    glGetProgramiv(program_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program_id, 1024, NULL, info_log);
        printf("| ERROR::Shader: Link-time error\n");
        printf("%s\n", info_log);
        printf("\n -- --------------------------------------------------- -- \n");
        return 1;
    }
    return 0;
}

int ShaderProgram::check_compile_success(ShaderType type){
	GLint success;
    GLchar info_log[1024];
    switch (type){
		case vertex: {
			glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &success);
			if (!success){
				glGetShaderInfoLog(vertex_id, 1024, NULL, info_log);
				printf("| ERROR::SHADER: Compile-time error: Type: vertex\n");
				printf("%s",info_log);
				printf("\n -- --------------------------------------------------- -- \n");
				return 1;
			}
			return 0;
			break;
		}
		case fragment: {
			glGetShaderiv(fragment_id, GL_COMPILE_STATUS, &success);
			if (!success){
				glGetShaderInfoLog(fragment_id, 1024, NULL, info_log);
				printf("| ERROR::SHADER: Compile-time error: Type: fragment\n");
				printf("%s",info_log);
				printf("\n -- --------------------------------------------------- -- \n");
				return 1;
			}
			return 0;
			break;
		}
		case geometry: {
			glGetShaderiv(geometry_id, GL_COMPILE_STATUS, &success);
			if (!success){
				glGetShaderInfoLog(geometry_id, 1024, NULL, info_log);
				printf("| ERROR::SHADER: Compile-time error: Type: geometry\n");
				printf("%s",info_log);
				printf("\n -- --------------------------------------------------- -- \n");
				return 1;
			}
			return 0;
			break;
		}
		default: {
			printf("Compile_check::unknown shader type!!\n");
			break;
		}
	}
	return 1;
}

ShaderProgram::~ShaderProgram(){
	glDeleteProgram(program_id);
}

int ShaderProgram::set_uniform_float (const GLchar *name, GLfloat value){
	if (is_used==false){
		return 1;
	}
	glUniform1f(glGetUniformLocation(program_id, name), value);
	return 0;
}

int ShaderProgram::set_uniform_integer (const GLchar *name, GLint value){
	if (is_used==false){
		return 1;
	}
	glUniform1i(glGetUniformLocation(program_id, name), value);
	return 0;
}

int ShaderProgram::set_uniform_vector2f (const GLchar *name, GLfloat x, 
										 GLfloat y)
{
	if (is_used==false){
		return 1;
	}
	glUniform2f(glGetUniformLocation(program_id, name), x, y);
	return 0;
}

int ShaderProgram::set_uniform_vector2f (const GLchar *name, const glm::vec2 &value){
	if (is_used==false){
		return 1;
	}
	glUniform2f(glGetUniformLocation(program_id, name), value.x, value.y);
	return 0;
}

int ShaderProgram::set_uniform_vector3f (const GLchar *name, GLfloat x,  
										 GLfloat y, GLfloat z)
{
	if (is_used==false){
		return 1;
	}
	glUniform3f(glGetUniformLocation(program_id, name), x, y, z);
	return 0;
}

int ShaderProgram::set_uniform_vector3f (const GLchar *name, const glm::vec3 &value){
	if (is_used==false){
		return 1;
	}
	glUniform3f(glGetUniformLocation(program_id, name), value.x, value.y, value.z);
	return 0;
}

int ShaderProgram::set_uniform_vector4f (const GLchar *name, GLfloat x, 
										GLfloat y, GLfloat z, GLfloat w)
{
	if (is_used==false){
		return 1;
	}
	glUniform4f(glGetUniformLocation(program_id, name), x, y, z, w);
	return 0;
}

int ShaderProgram::set_uniform_vector4f (const GLchar *name, const glm::vec4 &value){
	if (is_used==false){
		return 1;
	}
	glUniform4f(glGetUniformLocation(program_id, name), value.x, value.y, value.z, value.w);
	return 0;
}

int ShaderProgram::set_uniform_matrix4 (const GLchar *name, const glm::mat4 &matrix){
	if (is_used==false){
		return 1;
	}
	glUniformMatrix4fv(glGetUniformLocation(program_id, name), 1, GL_FALSE, glm::value_ptr(matrix));
	return 0;
}

GLuint ShaderProgram::get_id(){
	return program_id;
}



