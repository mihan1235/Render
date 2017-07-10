#include <render.hpp>
#include <camera.h>

namespace {
	int SCR_WIDTH = 800;
	int SCR_HEIGHT = 600;
	// Camera
	Camera camera(glm::vec3(0.0f, 3.0f, 3.0f));
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;
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
	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "GLFW Proba", monitor, NULL);
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
	// Initialize GLEW to setup the OpenGL Function pointers
	glewExperimental = GL_TRUE;
	glewInit();
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
	return glm::perspective(camera.Zoom, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
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