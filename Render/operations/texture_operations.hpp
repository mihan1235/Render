#pragma once
#include <GL\glew.h>

namespace kr {
	GLuint prepare_texture(const char* name);
	GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);
}