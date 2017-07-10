#pragma once
#include <GL/glew.h>

GLuint load_texture(GLchar const * path);
GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);
