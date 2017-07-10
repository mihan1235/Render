#include <light.hpp>
#include <core.hpp>

namespace {
	glm::vec3 light_position = glm::vec3(1.2f, 20.0f, -14.0f);
	glm::vec3 light_color = glm::vec3(0.3f, 0.3f, 0.3f);
	glm::vec3 diffuseColor = light_color;// * glm::vec3(0.5f); // Decrease the influence
	glm::vec3 ambientColor = diffuseColor;//* glm::vec3(0.2f); // Low influence
	glm::vec3 light_specular = glm::vec3(0.5f, 0.5f, 0.5f);
}

glm::vec3 kr::get_light_position() {
	return light_position;
}

glm::mat4 kr::get_light_space_ortho_matrix() {
	///set light space matrix
	GLfloat near_plane = 1.0f, far_plane = 700.5f;
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	glm::mat4 lightView = glm::lookAt(light_position, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 lightSpaceMatrix = lightProjection * lightView;
	return lightSpaceMatrix;
}

glm::mat4 kr::get_light_space_perspective_matrix() {
	//set lightSpaceMatrix
	glm::vec3 front = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 lightView = glm::lookAt(light_position, light_position + front, Up);
	GLfloat aspect = Core::get_width() / Core::get_height();
	glm::mat4 lightProjection = glm::perspective(45.0f, aspect, 0.1f, 1000.0f);
	glm::mat4 lightSpaceMatrix = lightProjection * lightView;
	return lightSpaceMatrix;
}

glm::vec3 kr::get_light_color() {
	return light_color;
}

glm::vec3 kr::get_light_diffuse_color() {
	return diffuseColor;
}

glm::vec3 kr::get_light_ambient_color() {
	return ambientColor;
}

glm::vec3 kr::get_light_specular_color() {
	return light_specular;
}
