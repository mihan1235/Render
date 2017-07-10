#pragma once
#include <GLFW/glfw3.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void react_on_keys();

GLboolean& get_shadow_option();
GLboolean& get_normal_map_option();
GLboolean& get_effect_option();