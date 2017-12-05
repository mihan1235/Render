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

#include <resource_manager.hpp>
#include <physics_manager.hpp>
#include <screen_buffer_object.hpp>

#include <string>
#include <vector>
#include <texture_operations.hpp>

// Global variables
GLuint woodTexture;
GLuint planeVAO;

// Light source
glm::vec3 lightPos(0.0f, 15.0f, 0.0f);

// The MAIN function, from here we start our application and run our Game loop
int main()
{
	//printf("OK\n");
	init_glfw();
	GLFWwindow* window=create_window();
	set_callback_functions(window);
	set_cursor(window);
	init_glew();
	setup_opengl(window);
	ResourceManager res_manager;
	init_objects();
	set_debug_drawer();
	Shader shader = Shader("point_shadows.vert", "point_shadows.frag");
	Shader simpleDepthShader = Shader("point_shadows_depth.vert", "point_shadows_depth.frag", "point_shadows_depth.geom");
	// Set texture samples
	shader.Use();
	// Configure depth map FBO
	const GLuint SHADOW_WIDTH = get_scr_width(), SHADOW_HEIGHT = get_scr_width();
	GLuint depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	// Create depth cubemap texture
	GLuint depthCubemap;
	glGenTextures(1, &depthCubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
	for (GLuint i = 0; i < 6; ++i) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// Attach cubemap as depth map FBO's color buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "Framebuffer not complete!" << std::endl;
	}
		
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	ScreenBufferObject screen_buffer;

	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	Shader skyboxShader = Shader("skybox.vert","skybox.frag");

	// skybox VAO
	unsigned int skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// loads a cubemap texture from 6 individual texture faces
	// order:
	// +X (right)
	// -X (left)
	// +Y (top)
	// -Y (bottom)
	// +Z (front) 
	// -Z (back)
	// -------------------------------------------------------
	std::vector<std::string> faces
	{
		"envmap_miramar/miramar_right.tga",
		"envmap_miramar/miramar_left.tga",
		"envmap_miramar/miramar_top.tga",
		"envmap_miramar/miramar_bottom.tga",
		"envmap_miramar/miramar_front.tga",
		"envmap_miramar/miramar_back.tga"
		
	};
	

	unsigned int cubemapTexture = loadCubemap(faces);

	

	
	//Camera& cam = get_camera();
	while (!glfwWindowShouldClose(window))
	{
		set_frame_time();
		start_simulation_step();
		// Check and call events
		glfwPollEvents();
		react_on_keys();
		glClearColor(0.1f, 0.5f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		 //Move light position over time
		//lightPos.z = sin(glfwGetTime() * 0.5) * 3.0;

		// 0. Create depth cubemap transformation matrices
		GLfloat aspect = (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT;
		GLfloat near = 0.1f;
		GLfloat far = 1000.0f;
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
		for (GLuint i = 0; i < 6; ++i) {
			simpleDepthShader.setMat4(("shadowTransforms[" + std::to_string(i) + "]").c_str(), shadowTransforms[i]);
		}
		simpleDepthShader.setFloat("far_plane", far);
		simpleDepthShader.setVec3("lightPos", lightPos);
		draw_objects(simpleDepthShader);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//glDrawBuffer(GL_NONE);
		//glReadBuffer(GL_NONE);
		

		// 2. Render scene as normal 

		glViewport(0, 0, get_scr_width(), get_scr_height());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.Use();
		//glm::mat4 projection = get_projection();
		glm::mat4 view = get_view_matrix();
		shader.setMat4("projection",get_projection());
		shader.setMat4("view",view);
		// Set light uniforms
		shader.setVec3("lightPos",lightPos);
		shader.setVec3("viewPos",get_position());
		// Enable/Disable shadows by pressing 'SPACE'
		shader.setBool("shadows", get_shadow_option());
		shader.setFloat("far_plane", far);
		// Enable/Disable normal mapping by pressing 'n'
		shader.setBool("normalMapping", get_normal_map_option());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
		screen_buffer.bind_to_our_framebuffer();
		draw_objects(shader);
		glFlush();
		if (get_debug_option()) {
			draw_debug_drawer();
		}
		
		/////////////////////////////////////
		glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
		skyboxShader.Use();
		// ... set view and projection matrix
		skyboxShader.setMat4("view", glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) + get_front(), get_up()));
		GLfloat aspect_1 = get_scr_width() / get_scr_height();
		skyboxShader.setMat4("projection", glm::perspective(get_zoom(), aspect_1, 0.1f, 1000.0f));
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // set depth function back to default
		///////////////////////////////////////
		screen_buffer.bind_to_default_framebuffer();
		screen_buffer.draw();
		// Swap the buffers
		glfwSwapBuffers(window);
		show_fps(window);
	}
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);
	glfwTerminate();
	return 0;
}

