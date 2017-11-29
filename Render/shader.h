#pragma once

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <glm\glm.hpp>

class Shader
{
public:
	GLuint Program;
	// Constructor generates the shader on the fly
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath = nullptr);
	// Uses the current shader
	void Use();
	void setBool(const std::string &name, bool value)const;
	void setInt(const std::string &name, int value)const;
	void setFloat(const std::string &name, float value) const;
	void setVec2(const std::string &name, const glm::vec2 &value) const;
	void setVec2(const std::string &name, float x, float y) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec4(const std::string &name, const glm::vec4 &value) const;
	void setVec4(const std::string &name, float x, float y, float z, float w);
	void setMat2(const std::string &name, const glm::mat2 &mat) const;
	void setMat3(const std::string &name, const glm::mat3 &mat) const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
private:
	void checkCompileErrors(GLuint shader, std::string type);
	

};

