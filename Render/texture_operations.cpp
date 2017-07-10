#include <texture_operations.hpp>
// Other Libs
#include <FreeImage.h>

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