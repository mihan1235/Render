#include <render.hpp>
#include <camera.h>
#include <sstream>

namespace {
	int SCR_WIDTH = 1600;
	int SCR_HEIGHT = 900;
	// Camera
	Camera camera(glm::vec3(0.0f, 13.0f, 14.0f));
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;
	bool glew_init = false;

	int num_frames = 0;
	int last_time = 0;
}

int get_scr_width() {
	return SCR_WIDTH;
}

int get_scr_height() {
	return SCR_HEIGHT;
}

void init_glfw() {
	// Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

GLFWwindow*  create_window() {
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	//GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Render", monitor, NULL);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Render", NULL, NULL);
	glfwMakeContextCurrent(window);
	return window;
}

void set_callback_functions(GLFWwindow* window) {
	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
}

void set_cursor(GLFWwindow* window) {
	// Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void init_glew() {
	if (glew_init == false) {
		// Initialize GLEW to setup the OpenGL Function pointers
		glewExperimental = GL_TRUE;
		glewInit();
		glew_init = true;
	}
}

void setup_opengl(GLFWwindow* window) {

	// Define the viewport dimensions
	glfwGetFramebufferSize(window, &SCR_WIDTH, &SCR_HEIGHT);
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

glm::mat4 get_projection() {
	return glm::perspective(camera.Zoom, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
}

glm::mat4 get_view_matrix() {
	return camera.GetViewMatrix();
}

glm::vec3 get_position() {
	return camera.Position;
}

Camera& get_camera() {
	return camera;
}

GLfloat& get_delta_time() {
	return deltaTime;
}

GLfloat& get_last_frame() {
	return lastFrame;
}

void set_frame_time() {
	// Set frame time
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void show_fps(GLFWwindow* window) {
	// Measure speed
	double current_time = glfwGetTime();
	double delta = current_time - last_time;
	num_frames++;
	if (delta >= 1.0) { // If last cout was more than 1 sec ago
						//cout<< "num_frames: "<<num_frames<<endl;
						//cout << 1000.0/double(num_frames) << endl;
		double fps = double(num_frames) / delta;
		std::stringstream ss;
		ss << "GLFW Proba" << " [" << fps << " FPS]";
		glfwSetWindowTitle(window, ss.str().c_str());
		num_frames = 0;
		last_time = current_time;
	}
}