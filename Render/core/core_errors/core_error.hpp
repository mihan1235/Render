#pragma once
#include <string>
#include <error/error.hpp>

namespace kr{
	class ErrCore: public Error{
	public:
		ErrCore() throw(){};
	};
	
	class ErrGlfwInit: public ErrCore{
	public:
		ErrGlfwInit()throw(){};
		const char* what() const throw(){
			return "Couldn't initialize glfw\n";
		}
	};
	
	class ErrWindow: public ErrCore{
	public:
		ErrWindow() throw(){};
		const char* what() const throw(){
			return "Couldn't create window \"GLFW Proba\"\n";
		}
	};
	
	class ErrGlewInit: public ErrCore{
	public:
		ErrGlewInit() throw(){};
		const char* what() const throw(){
			return "Failed to initialize GLEW";
		}
	};
}
