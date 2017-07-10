#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <camera_movement.hpp>

namespace kr{
	// Default camera values
	const GLfloat YAW        = -90.0f;
	const GLfloat PITCH      =  0.0f;
	const GLfloat SPEED      =  30.0f;
	const GLfloat SENSITIVTY =  0.25f;
	const GLfloat ZOOM       =  45.0f;

	// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
	class Camera
	{
	public:
		// Camera Attributes
		static glm::vec3 Position;
		static glm::vec3 front;
		static glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;
		// backed up camera vectors
		glm::vec3 front_back_up;
		glm::vec3 Up_back_up;
		glm::vec3 Right_back_up;
		///////////////////////////
		// Eular Angles
		GLfloat Yaw;
		GLfloat Pitch;
		// Camera options
		GLfloat MovementSpeed;
		GLfloat sensitivity;
		static GLfloat Zoom;

		// Constructor with vectors
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
		       glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
		       GLfloat yaw = YAW, GLfloat pitch = PITCH);
		// Constructor with scalar values
		Camera(GLfloat posX, GLfloat posY, GLfloat posZ,
		       GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, 
		       GLfloat pitch);
		// Returns the view matrix calculated using Eular Angles and 
		// the LookAt Matrix
		static glm::mat4 get_view_matrix();
		// Processes input received from any keyboard-like input system.
		// Accepts input parameter in the form of camera defined ENUM 
		// (to abstract it from windowing systems)
		void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
		// Processes input received from a mouse input system. Expects 
		// the offset value in both the x and y direction.
		void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, 
		                          GLboolean constrainPitch = true);
		// Processes input received from a mouse scroll-wheel event. 
		// Only requires input on the vertical wheel-axis
		void ProcessMouseScroll(GLfloat yoffset);
		static glm::mat4 get_projection_matrix();
		static glm::vec3 get_position(){
			return Position;
		}
	private:
		// Calculates the front vector from the Camera's (updated) 
		// Eular Angles
		void update_camera_vectors();
	};
}
