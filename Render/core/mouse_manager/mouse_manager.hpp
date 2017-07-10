#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <queue>
#include <cursor_position.hpp>
#include <scroll_offset.hpp>

namespace kr{
	class MouseManager{

	public:
		MouseManager(){};
		~MouseManager(){};
	private:
		MouseManager(const MouseManager&);
		MouseManager& operator=(const MouseManager&) {};
	protected:
		static void cursor_callback(GLFWwindow*,double x_pos, double y_pos);
		static void scroll_callback(GLFWwindow* window, double x_offset, double y_offset);
		static std::queue<CursorPosition> cursor_position_queue;
		static std::queue<ScrollOffset> scroll_offset_queue;
		virtual void react_mouse_movement()=0;
		virtual void react_scroll_movement()=0;
	};
}
