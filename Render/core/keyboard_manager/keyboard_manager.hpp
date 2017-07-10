#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <queue>

namespace kr{
	class KeyboardManager{
		
	public:
		KeyboardManager(){};
		~KeyboardManager(){};
	private:
		KeyboardManager(const KeyboardManager&);
		KeyboardManager& operator=(const KeyboardManager&) {};
	protected:
		static void key_callback(GLFWwindow*,int,int,int,int);
		static std::queue<int> key_pressed_queue;
		/*bool alt_pressed=false;*/
		virtual void react_key_pressed()=0;
	};
}
