#include <core/core.hpp>
#include <iostream>
#include <sstream>
#include <core/core_errors/core_error.hpp>
#include <cstdio>

#include <resource_manager.hpp>
#include <screen_buffer_object.hpp>
#include <depth_buffer.hpp>


using namespace kr;
using std::cout;
using std::endl;

int Core::width=800;
int Core::height=600;
GLfloat  Core::delta_time = 0.0f;

Core& Core::Instance(){
	static Core new_single_core;
	return new_single_core;
}

void Core::react_key_pressed(){
	int key;
	while (!key_pressed_queue.empty()){
		key=key_pressed_queue.front();
		//printf("key: %i\n",key);
		switch (key){
			/*case GLFW_KEY_LEFT_ALT:
			case GLFW_KEY_RIGHT_ALT: {
				alt_pressed=!alt_pressed;
				break;
			}*/
			/*case GLFW_KEY_ENTER: 
			case GLFW_KEY_KP_ENTER:{
				if (alt_pressed){
					if (fullscreen_mode){
						exit_fullscreen_mode();
					}
					else{
						enter_fullscreen_mode();
					}
					alt_pressed=!alt_pressed;
				}
				break;
			}*/
			case GLFW_KEY_W:{
				camera.ProcessKeyboard(FORWARD, delta_time);
				//goto switch_default;
				break;
			}
			case GLFW_KEY_S:{
				camera.ProcessKeyboard(BACKWARD, delta_time);
				//goto switch_default;
				break;
			}
			case GLFW_KEY_A:{
				camera.ProcessKeyboard(LEFT, delta_time);
				//goto switch_default;
				break;
			}
			case GLFW_KEY_D:{
				camera.ProcessKeyboard(RIGHT, delta_time);
				//goto switch_default;
				break;
			}
			case GLFW_KEY_V: {
				ScreenBufferObject::use_effect=!ScreenBufferObject::use_effect;
				break;
			}
			//default://{
				//switch_default:
				/*	if (alt_pressed){
						alt_pressed=!alt_pressed;
					}*/
			//}
		}
		key_pressed_queue.pop();
	}
}

void Core::react_mouse_movement(){
	CursorPosition tmp1;
	while(!cursor_position_queue.empty()){
		tmp1=cursor_position_queue.front();
		//printf("x_pos: %lf, y_pos: %lf\n",tmp1.x_pos,tmp1.y_pos);
		//printf("x_offset: %lf, y_offset: %lf\n",tmp1.x_offset,tmp1.y_offset);
		camera.ProcessMouseMovement(tmp1.x_offset,tmp1.y_offset);
		glfwSetCursorPos(window,get_width()/2,get_height()/2);
		cursor_position_queue.pop();
	}
}

void Core::react_scroll_movement(){
	ScrollOffset tmp;
	while(!scroll_offset_queue.empty()){
		tmp=scroll_offset_queue.front();
		camera.ProcessMouseScroll(tmp.y_offset);
		scroll_offset_queue.pop();
	}
}

void Core::launch(){
	//////////////////////////////////
	printf("before_loop\n");
	//////////////////////////////////
	glEnable(GL_DEPTH_TEST);
	// Draw as wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	ResourceManager resource_manager;
	resource_manager.init_objects();
	resource_manager.add_objects_to_physics_manager(physics_manager);
	


	ScreenBufferObject screen_buffer;
	/*if (ScreenBufferObject::is_used()) {
		printf("true\n");
	}*/
    GLfloat current_frame;
	DepthBuffer depth_buffer;
	while (!glfwWindowShouldClose(window)){
		current_frame=glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame=current_frame;
		react_key_pressed();
		react_mouse_movement();
		react_scroll_movement();
		//glfwGetFramebufferSize(window, &width, &height);
		glfwPollEvents();
		//glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		physics_manager.start_simulation_step();
		////////////////////////////////////////
		depth_buffer.bind_to_our_framebuffer();
		depth_buffer.set_shaders_parameters();
		resource_manager.draw_objects(depth_buffer.get_shader_program());
		glFlush();
		depth_buffer.bind_to_default_framebuffer();
		/////////////////////////////////
		screen_buffer.bind_to_our_framebuffer();
		/////////////////////////////////
		resource_manager.draw_objects();
		//depth_buffer.debug_draw();
		/////////////////////////////////
		glFlush();
		screen_buffer.bind_to_default_framebuffer();
		screen_buffer.draw();
		glfwSwapBuffers(window);
        show_fps();
	}
	////////////////////////////////////
	printf("after_loop\n");
	
	////////////////////////////////////
}


Core::Core():camera(glm::vec3(0.0f, 20.0f, 28.0f)){
	/*fullscreen_mode=false;*/
	if (glfwInit()==0){
		throw(ErrGlfwInit());
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	/*window = glfwCreateWindow(1024,768,"GLFW Proba", nullptr, nullptr);
	glfwSetWindowSizeLimits(window,1024,768,GLFW_DONT_CARE,GLFW_DONT_CARE);*/
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	window = glfwCreateWindow(mode->width, mode->height, "GLFW Proba", monitor, NULL);
	if (window==nullptr){
		throw(ErrWindow());
	}
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, Core::get_width() / 2, Core::get_height() / 2);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        throw(ErrGlewInit());
    }  
}

Core::~Core(){
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Core::show_fps()
{
    // Measure speed
     double current_time = glfwGetTime();
     double delta = current_time - last_time;
     num_frames++;
     if ( delta >= 1.0 ){ // If last cout was more than 1 sec ago
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

//void Core::enter_fullscreen_mode(){
//	save_window_pos();
//	save_window_resolution();
//	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
//	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
//	glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, 
//						 mode->height, mode->refreshRate);
//	printf("===> entered fullscreen mode\n");
//	fullscreen_mode=true;
//}
//
//void Core::exit_fullscreen_mode(){
//	glfwSetWindowMonitor(window, nullptr, x_pos, y_pos, saved_width, 
//						saved_height, 0);
//	printf("<=== exited fullscreen mode\n");
//	fullscreen_mode=false;
//}
//
//void Core::save_window_pos(){
//	glfwGetWindowPos(window, &x_pos, &y_pos);
//}
//
//void Core::save_window_resolution(){
//	glfwGetWindowSize(window, &saved_width, &saved_height);
//}


