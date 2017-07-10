#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <keyboard_manager.hpp>
#include <mouse_manager.hpp>
#include <camera.hpp>
#include <physics_manager.hpp>
#include <resource_manager.hpp>

namespace kr{
	class Core: public KeyboardManager,MouseManager
	{
		static int width;
		static int height;
		/*int saved_width;
		int saved_height;*/
		int x_pos;
		int y_pos;
		int num_frames=0;
		int last_time=0;
		GLFWwindow* window;
		/*bool fullscreen_mode;*/
		static GLfloat delta_time;
		GLfloat last_frame = 0.0f;
		Camera camera;
		PhysicsManager physics_manager;
	public:
		virtual ~Core();
		static Core& Instance();
		virtual void launch();
		static GLfloat get_width(){
			return (GLfloat)width;
		}
		static GLfloat get_height(){
			return (GLfloat)height;
		}
		static GLfloat get_delta_time(){
			return delta_time;
		}
	private:
		Core();
        Core(const Core&);
		Core& operator=(const Core&) {};
        //virtual void render_frame();
        void show_fps();
        /*void enter_fullscreen_mode();
        void exit_fullscreen_mode();
        void save_window_pos();
        void save_window_resolution();*/
        void react_key_pressed();
        void react_mouse_movement();
        void react_scroll_movement();
	};
}
