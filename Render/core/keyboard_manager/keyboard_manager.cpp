#include <core/keyboard_manager/keyboard_manager.hpp>

using namespace kr;
std::queue<int> KeyboardManager::key_pressed_queue;

void KeyboardManager::key_callback(GLFWwindow* window, int key, int scancode,
							   int action, int mods)
{
	if ((action == GLFW_PRESS)||(action==GLFW_REPEAT)){
		switch (key){
			case GLFW_KEY_ESCAPE: {
				glfwSetWindowShouldClose(window, GL_TRUE);
				break;
			}
			default:{
				key_pressed_queue.push(key);
			}
		}
	}
}


