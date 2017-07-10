#include <depth_buffer.hpp>
#include <texture_operations.hpp>
#include <core.hpp>
#include <light.hpp>
#include <resource_manager.hpp>

using namespace kr;


DepthBuffer::DepthBuffer(){
	set_shaders_sources();
	shader_program = new ShaderProgram(vertex_shader_source, fragment_shader_source);
	debugDepthQuad = new ShaderProgram(vertex_shader_source_debug, fragment_shader_source_debug);
	glGenFramebuffers(1, &depthMapFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
		ResourceManager::get_texture("depthMap"), 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	////////////////////////////////////////////
	// for debug rendering
	////////////////////////////////////////////
	GLfloat quadVertices[] = {
		// Positions        // Texture Coords
		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
		1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
	};
	// Setup plane VAO
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	////////////////////////////////////////////
}

DepthBuffer::~DepthBuffer(){
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);
	delete vertex_shader_source;
	delete fragment_shader_source;
	delete shader_program;
	delete debugDepthQuad;
	delete vertex_shader_source_debug;
	delete fragment_shader_source_debug;
}

void DepthBuffer::bind_to_our_framebuffer() {
	glViewport(0, 0, Core::get_width(), Core::get_height());
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void DepthBuffer::bind_to_default_framebuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// Reset viewport	
	glViewport(0, 0, Core::get_width(), Core::get_height());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DepthBuffer::set_shaders_parameters() {
	//shader_program->use();
	
}


void DepthBuffer::set_shaders_sources() {
	vertex_shader_source = read_shader_file("data/shaders/depth_buffer/depth_buffer.vert");
	fragment_shader_source = read_shader_file("data/shaders/depth_buffer/depth_buffer.frag");
	vertex_shader_source_debug = read_shader_file("data/shaders/depth_buffer/depth_buffer_debug.vert");
	fragment_shader_source_debug = read_shader_file("data/shaders/depth_buffer/depth_buffer_debug.frag");
}

ShaderProgram* DepthBuffer::get_shader_program() {
	return shader_program;
}

void DepthBuffer::debug_draw() {
	////////////////////////////////
	//prepare
	////////////////////////////////
	debugDepthQuad->use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ResourceManager::get_texture("depthMap"));
	//////////////////////////////////
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}