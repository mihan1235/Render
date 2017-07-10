#include <texture_operations.hpp>
// Other Libs
#include <FreeImage.h>
#include <render.hpp>

// This function loads a texture from file. Note: texture loading functions like these are usually 
// managed by a 'Resource Manager' that manages all resources (like textures, models, audio). 
// For learning purposes we'll just define it as a utility function.
GLuint load_texture(GLchar const * name) {
	// Load image, create texture and generate mipmaps
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(name, 0);
	FIBITMAP* image = FreeImage_Load(format, name);
	FIBITMAP* temp = image;
	image = FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(temp);
	int width_tex = FreeImage_GetWidth(image);
	int height_tex = FreeImage_GetHeight(image);
	GLubyte* bits = FreeImage_GetBits(image);
	///////////////////////////////////////////////////
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// All upcoming GL_TEXTURE_2D operations now have effect on
	// this texture object
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_tex, height_tex, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);
	glGenerateMipmap(GL_TEXTURE_2D);
	FreeImage_Unload(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil) {
	// What enum to use?
	GLenum attachment_type;
	if (!depth && !stencil) {
		attachment_type = GL_RGB;
	}
	else {
		if (depth && !stencil) {
			attachment_type = GL_DEPTH_COMPONENT;
		}
		else {
			if (!depth && stencil) {
				attachment_type = GL_STENCIL_INDEX;
			}
		}
	}
	//Generate texture ID and load texture data 
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	if (!depth && !stencil) {
		glTexImage2D(GL_TEXTURE_2D, 0, attachment_type, get_scr_width(), get_scr_height(),
			0, attachment_type, GL_UNSIGNED_BYTE, NULL);
	}
	else {
		// Using both a stencil and depth test, needs special format arguments
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, get_scr_width(), get_scr_height(),
			0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}