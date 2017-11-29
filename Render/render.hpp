#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <poll_events.hpp>
#include <camera.h>

int get_scr_width();
int get_scr_height();
void init_glfw();
GLFWwindow* create_window();
void set_callback_functions(GLFWwindow* window);
void set_cursor(GLFWwindow* window);
void init_glew();
void setup_opengl(GLFWwindow* window);

glm::mat4 get_projection();
glm::mat4 get_view_matrix();
glm::vec3 get_position();

Camera& get_camera();

GLfloat& get_delta_time();
GLfloat& get_last_frame();

void set_frame_time();
void show_fps(GLFWwindow* window);