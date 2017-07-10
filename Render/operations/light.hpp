#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace kr {
	glm::vec3 get_light_position();
	glm::mat4 get_light_space_ortho_matrix();
	glm::mat4 get_light_space_perspective_matrix();
	glm::vec3 get_light_color();
	glm::vec3 get_light_diffuse_color();
	glm::vec3 get_light_ambient_color();
	glm::vec3 get_light_specular_color();
}
