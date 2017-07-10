#include <camera.hpp>
#include <core.hpp>

using namespace kr;

// Constructor with vectors
Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch)
{
	front=glm::vec3(0.0f, 0.0f, -1.0f);
	MovementSpeed=SPEED;
	sensitivity=SENSITIVTY;
	this->Position = position;
	this->WorldUp = up;
	this->Yaw = yaw;
	this->Pitch = pitch;
	update_camera_vectors();
}

// Constructor with scalar values
Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, 
               GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch)
{
	MovementSpeed=SPEED;
	sensitivity=SENSITIVTY;
	front=glm::vec3(0.0f, 0.0f, -1.0f);
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	this->Yaw = yaw;
	this->Pitch = pitch;
	update_camera_vectors();
}

// Returns the view matrix calculated using Eular Angles and the LookAt 
// Matrix

glm::mat4 Camera::get_view_matrix()
{
	return glm::lookAt(Position, Position + front, Up);
}

// Processes input received from any keyboard-like input system. 
//Accepts input parameter in the form of camera defined ENUM 
//(to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
	GLfloat velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position += front * velocity;
	if (direction == BACKWARD)
		Position -= front * velocity;
	if (direction == LEFT)
		Position -= Right * velocity;
	if (direction == RIGHT)
		Position += Right * velocity;
	//you cannot fly
	//you can only look around while staying on the xz plane
	//this->Position.y = 0.0f;
}

// Processes input received from a mouse input system. Expects the 
//offset value in both the x and y direction.
void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, 
                                  GLboolean constrainPitch)
{
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	Yaw   += xoffset;
	Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get 
	//flipped
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	update_camera_vectors();
}

// Processes input received from a mouse scroll-wheel event. Only 
// requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(GLfloat yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset* sensitivity;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}

glm::mat4 Camera::get_projection_matrix(){
	glm::mat4 projection;
	GLfloat aspect= Core::get_width()/Core::get_height();
	projection = glm::perspective(glm::radians(Zoom), aspect, 0.1f, 1000.0f);
	return projection;
}


// Calculates the front vector from the Camera's (updated) Eular Angles
void Camera::update_camera_vectors()
{
	// Calculate the new Front vector
	//glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	this->front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(this->front, WorldUp));  
	// Normalize the vectors, because their length gets closer to 0 
	// the more you look up or down which results in slower movement.
	Up    = glm::normalize(glm::cross(Right, this->front));
}

glm::vec3 Camera::Position;
glm::vec3 Camera::front;
glm::vec3 Camera::Up;
GLfloat Camera::Zoom=ZOOM;


