#pragma once
#include <GL/glew.h>
#include <object.hpp>

namespace kr {
	class DepthBuffer
	{
		GLuint depthMapFBO;
		GLuint quadVAO;
		GLuint quadVBO;
		ShaderProgram* shader_program;
		ShaderProgram* debugDepthQuad;
		const GLchar* vertex_shader_source;
		const GLchar* fragment_shader_source;
		const GLchar* vertex_shader_source_debug;
		const GLchar* fragment_shader_source_debug;
	public:
		DepthBuffer();
		~DepthBuffer();
		void bind_to_our_framebuffer();
		void bind_to_default_framebuffer();
		void set_shaders_parameters();
		ShaderProgram* get_shader_program();
		void debug_draw();
	private:
		void set_shaders_sources();
	};
}