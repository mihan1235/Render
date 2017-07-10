#include <screen_buffer_object.hpp>
#include <iostream>
#include <texture_operations.hpp>
#include <render.hpp>

ScreenBufferObject::ScreenBufferObject() {	
	GLfloat vertices[] = {
		// Vertex attributes for a quad that fills the entire screen in Normalized
		// Device Coordinates.
		// Positions   // TexCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};
	//GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glBindVertexArray(0);

	//FrameBuffer
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	// Create a color attachment texture
	textureColorbuffer = generateAttachmentTexture(false, false);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	// Create a renderbuffer object for depth and stencil attachment (we won't be sampling these)

	//GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,get_scr_width(), get_scr_height());
	// Use a single renderbuffer object for both a depth AND stencil buffer.
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	// Now actually attach it
	// Now that we actually created the framebuffer and added all attachments we want to check 
	// if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ScreenBufferObject::draw() {
	// Draw Screen
	// Enable/Disable screen effect by pressing 'v'
	screen_shader.Use();
	glUniform1i(glGetUniformLocation(screen_shader.Program, "effect"), get_effect_option());
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	// Use the color attachment texture as the texture of the quad plane
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}



ScreenBufferObject::~ScreenBufferObject() {
	// Clean up
	glDeleteFramebuffers(1, &framebuffer);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void ScreenBufferObject::bind_to_our_framebuffer() {
	/////////////////////////////////////////////////////
	// Bind to framebuffer and draw to color texture 
	// as we normally would.
	// //////////////////////////////////////////////////
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	// Clear all attached buffers        
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// We're not using stencil buffer so why bother with clearing?
	//glEnable(GL_DEPTH_TEST);
}

void ScreenBufferObject::bind_to_default_framebuffer() {
	/////////////////////////////////////////////////////
	// Bind to default framebuffer again and draw the 
	// quad plane with attched screen texture.
	// //////////////////////////////////////////////////
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// Clear all relevant buffers
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Set clear color to white 
	// (not really necessery actually, since we won't be 
	// able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT);
	//glDisable(GL_DEPTH_TEST);
	// We don't care about depth information when rendering a single quad

}