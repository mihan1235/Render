
#include <render.hpp>
#include<poll_events.hpp>
#include <physics_manager.hpp>
namespace {
	// Options
	GLboolean shadows = true;
	GLboolean normalMapping = true;
	GLboolean effect = false;
	GLboolean DBG_DrawWireframe = false;
	GLboolean DBG_DrawAabb = false;
}



bool keys[1024];
bool keysPressed[1024];
Camera& camera = get_camera();
GLfloat& deltaTime = get_delta_time();


// Moves/alters the camera positions based on user input
void react_on_keys()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);

	if (keys[GLFW_KEY_SPACE] && !keysPressed[GLFW_KEY_SPACE])
	{
		shadows = !shadows;
		keysPressed[GLFW_KEY_SPACE] = true;
	}

	if (keys[GLFW_KEY_N] && !keysPressed[GLFW_KEY_N])
	{
		normalMapping = !normalMapping;
		keysPressed[GLFW_KEY_N] = true;
	}

	if (keys[GLFW_KEY_V] && !keysPressed[GLFW_KEY_V])
	{
		effect = !effect;
		keysPressed[GLFW_KEY_V] = true;
	}
	BtDebugDrawer* m_pDebugDrawer = get_debug_drawer();
	if (keys[GLFW_KEY_U] && !keysPressed[GLFW_KEY_U])
	{
		DBG_DrawWireframe = !DBG_DrawWireframe;
		m_pDebugDrawer->ToggleDebugFlag(btIDebugDraw::DBG_DrawWireframe);
		keysPressed[GLFW_KEY_U] = true;
	}
	if (keys[GLFW_KEY_I] && !keysPressed[GLFW_KEY_I])
	{
		DBG_DrawAabb = !DBG_DrawAabb;
		m_pDebugDrawer->ToggleDebugFlag(btIDebugDraw::DBG_DrawAabb);
		keysPressed[GLFW_KEY_I] = true;
	}
}

GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;
// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key <= 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
			keysPressed[key] = false;
		}
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

GLboolean& get_shadow_option() {
	return shadows;
}

GLboolean& get_normal_map_option() {
	return normalMapping;
}

GLboolean& get_effect_option() {
	return effect;
}

GLboolean get_debug_option() {
	if (DBG_DrawWireframe | DBG_DrawAabb) {
		return true;
	}
	else {
		false;
	}
}