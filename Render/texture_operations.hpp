#pragma once
#include <GL/glew.h>
#include <vector>

GLuint load_texture(GLchar const * path);
GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);
unsigned int loadCubemap(std::vector<std::string> faces);
