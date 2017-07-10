#pragma once
#include <shader.h>


class ScreenBufferObject {
	Shader screen_shader = Shader("screen_buffer_vertex_shader.vert", "screen_buffer_fragment_shader.frag");
	GLuint VBO, VAO;
	GLuint rbo;
	GLuint framebuffer;
	GLuint textureColorbuffer;
public:
	ScreenBufferObject();
	void draw();
	~ScreenBufferObject();
	void bind_to_our_framebuffer();
	void bind_to_default_framebuffer();
private:
	ScreenBufferObject(const ScreenBufferObject&) {};
	ScreenBufferObject& operator=(const ScreenBufferObject&) {};
protected:
};
