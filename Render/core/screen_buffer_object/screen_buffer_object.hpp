#pragma once
#include <object.hpp>

namespace kr {
	class ScreenBufferObject {
		/*static int num_screen_buffer;*/
		ShaderProgram* shader_program_effect;
		ShaderProgram* shader_program_no_effect;
		const GLchar* vertex_shader_source;
		const GLchar* fragment_shader_source_effect;
		const GLchar* fragment_shader_source_no_effect;
		GLuint VBO, VAO;
		GLuint rbo;
		GLuint framebuffer;
		//GLuint textureColorbuffer;
	public:
		ScreenBufferObject();
		void draw();
		~ScreenBufferObject();
		void bind_to_our_framebuffer();
		void bind_to_default_framebuffer();
		/*static bool is_used() {
			if (num_screen_buffer > 0) {
				return true;
			}
			return false;
		}*/
		static bool use_effect;
	private:
		void set_shaders_sources();
		ScreenBufferObject(const ScreenBufferObject&) {};
		ScreenBufferObject& operator=(const ScreenBufferObject&) {};
	protected:
	};
}