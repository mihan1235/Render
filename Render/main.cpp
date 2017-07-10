// GLEW


#include <render.hpp>
#include <poll_events.hpp>

// GL includes
#include <shader.h>


// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <texture_operations.hpp>

#include <vector>

#include <objects.hpp>

#include <model.h>

// Function prototypes


void RenderScene(Shader &shader);








// Global variables
GLuint woodTexture;
GLuint planeVAO;
//Model zil_131 = Model("zil_131/zil_131.obj");


// The MAIN function, from here we start our application and run our Game loop
int main()
{
	init_glfw();
	GLFWwindow* window=create_window();
	set_callback_functions(window);
	set_cursor(window);
	init_glew();
	setup_opengl(window);

	// Setup and compile our shaders
	Shader shader("point_shadows.vert", "point_shadows.frag");
	Shader simpleDepthShader("point_shadows_depth.vert", "point_shadows_depth.frag", "point_shadows_depth.geom");

	// Set texture samples
	shader.Use();
	

	// Light source
	glm::vec3 lightPos(0.0f, 5.0f, 0.0f);

	// Load textures
	woodTexture = load_texture("wall_orange_01.dds");

	// Configure depth map FBO
	const GLuint SHADOW_WIDTH = get_scr_width(), SHADOW_HEIGHT = get_scr_width();
	GLuint depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	// Create depth cubemap texture
	GLuint depthCubemap;
	glGenTextures(1, &depthCubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
	for (GLuint i = 0; i < 6; ++i)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// Attach cubemap as depth map FBO's color buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);



	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		set_frame_time();

		// Check and call events
		glfwPollEvents();
		react_on_keys();
		// Move light position over time
		//lightPos.z = sin(glfwGetTime() * 0.5) * 3.0;

		// 0. Create depth cubemap transformation matrices
		GLfloat aspect = (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT;
		GLfloat near = 0.1f;
		GLfloat far = 100.0f;
		glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), aspect, near, far);
		std::vector<glm::mat4> shadowTransforms;
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

		// 1. Render scene to depth cubemap
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		simpleDepthShader.Use();
		for (GLuint i = 0; i < 6; ++i)
			glUniformMatrix4fv(glGetUniformLocation(simpleDepthShader.Program, ("shadowTransforms[" + std::to_string(i) + "]").c_str()), 1, GL_FALSE, glm::value_ptr(shadowTransforms[i]));
		glUniform1f(glGetUniformLocation(simpleDepthShader.Program, "far_plane"), far);
		glUniform3fv(glGetUniformLocation(simpleDepthShader.Program, "lightPos"), 1, &lightPos[0]);
		RenderScene(simpleDepthShader);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// 2. Render scene as normal 
		glViewport(0, 0, get_scr_width(), get_scr_height());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.Use();
		glm::mat4 projection = get_projection();
		glm::mat4 view = get_view_matrix();
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		// Set light uniforms
		glUniform3fv(glGetUniformLocation(shader.Program, "lightPos"), 1, &lightPos[0]);
		glUniform3fv(glGetUniformLocation(shader.Program, "viewPos"), 1, &get_position()[0]);
		// Enable/Disable shadows by pressing 'SPACE'
		glUniform1i(glGetUniformLocation(shader.Program, "shadows"), get_shadow_option());
		glUniform1f(glGetUniformLocation(shader.Program, "far_plane"), far);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, woodTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
		RenderScene(shader);
		// Swap the buffers
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}


void RenderScene(Shader &shader)
{
	glm::mat4 model;
	// Room cube
	
	//model = glm::scale(model, glm::vec3(10.0f));
	//glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	//glDisable(GL_CULL_FACE); // Note that we disable culling here since we render 'inside' the cube instead of the usual 'outside' which throws off the normal culling methods.
	//glUniform1i(glGetUniformLocation(shader.Program, "reverse_normals"), 1); // A small little hack to invert normals when drawing cube from the inside so lighting still works.
	//RenderCube();
	//glUniform1i(glGetUniformLocation(shader.Program, "reverse_normals"), 0); // And of course disable it
	//glEnable(GL_CULL_FACE);

	model = glm::mat4();
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform1i(glGetUniformLocation(shader.Program, "texture_diffuse1"), 0);
	glUniform1i(glGetUniformLocation(shader.Program, "depthMap"), 1);
	//glDisable(GL_CULL_FACE); // Note that we disable culling here since we render 'inside' the cube instead of the usual 'outside' which throws off the normal culling methods.
	//glUniform1i(glGetUniformLocation(shader.Program, "reverse_normals"), 1); // A small little hack to invert normals when drawing cube from the inside so lighting still works.
	RenderRectangle();
	//glUniform1i(glGetUniformLocation(shader.Program, "reverse_normals"), 0); // And of course disable it
	//glEnable(GL_CULL_FACE);
	// Cubes
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(4.0f, 3.5f, 0.0));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform1i(glGetUniformLocation(shader.Program, "texture_diffuse1"), 0);
	glUniform1i(glGetUniformLocation(shader.Program, "depthMap"), 1);
	RenderCube();
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(2.0f, 3.0f, 1.0));
	model = glm::scale(model, glm::vec3(1.5));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform1i(glGetUniformLocation(shader.Program, "texture_diffuse1"), 0);
	glUniform1i(glGetUniformLocation(shader.Program, "depthMap"), 1);
	RenderCube();
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(-3.0f, 1.0f, 0.0));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform1i(glGetUniformLocation(shader.Program, "texture_diffuse1"), 0);
	glUniform1i(glGetUniformLocation(shader.Program, "depthMap"), 1);
	RenderCube();
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(-1.5f, 1.0f, 1.5));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform1i(glGetUniformLocation(shader.Program, "texture_diffuse1"), 0);
	glUniform1i(glGetUniformLocation(shader.Program, "depthMap"), 1);
	RenderCube();
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(-1.5f, 2.0f, -3.0));
	model = glm::rotate(model, 60.0f, glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	model = glm::scale(model, glm::vec3(1.5));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform1i(glGetUniformLocation(shader.Program, "texture_diffuse1"), 0);
	glUniform1i(glGetUniformLocation(shader.Program, "depthMap"), 1);
	RenderCube();
	//model = glm::mat4();
	//model = glm::translate(model, glm::vec3(-6.0f, 2.0f, -3.0));
	////model = glm::rotate(model, 60.0f, glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	////model = glm::scale(model, glm::vec3(1.5));
	//glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	//zil_131.Draw(shader);
}


