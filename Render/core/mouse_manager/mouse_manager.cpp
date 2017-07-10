#include <mouse_manager.hpp>
#include <cstdio>
#include <core.hpp>

using namespace kr;

std::queue<CursorPosition> MouseManager::cursor_position_queue;
std::queue<ScrollOffset> MouseManager::scroll_offset_queue;

void MouseManager::cursor_callback(GLFWwindow* window,double x_pos, double y_pos){
	GLfloat x_offset=x_pos-Core::get_width()/2;
	GLfloat y_offset=y_pos-Core::get_height()/2;
	CursorPosition cur_pos;
	cur_pos.x_pos=x_pos;
	cur_pos.y_pos=y_pos;
	cur_pos.x_offset=x_offset;
	cur_pos.y_offset=y_offset;
	cursor_position_queue.push(cur_pos);
	//printf("x_pos: %f ; y_pos: %f ; x_offset: %f; y_offset: %f\n", x_pos, y_pos, x_offset, y_offset);
}

void MouseManager::scroll_callback(GLFWwindow* window, double x_offset, double y_offset){
	ScrollOffset scroll_off;
	scroll_off.x_offset=x_offset;
	scroll_off.y_offset=y_offset;
	scroll_offset_queue.push(scroll_off);
}

