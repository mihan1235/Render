#define _CRT_SECURE_NO_WARNINGS 

#include <file_operations.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>


const GLchar* kr::read_shader_file(const GLchar* path) {
	std::string code;
	std::ifstream shader_file;
	// ensures ifstream objects can throw exceptions:
	shader_file.exceptions(std::ifstream::badbit);
	try
	{
		// Open files
		shader_file.open(path);
		std::stringstream shader_stream;
		// Read file's buffer contents into streams
		shader_stream << shader_file.rdbuf();
		// close file handlers
		shader_file.close();
		// Convert stream into string
		code = shader_stream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	char * c_code = new char[code.size() + 1];
	strcpy(c_code, code.c_str());
	return c_code;
}