#include <rectangle.hpp>
#include <camera.hpp>
#include <GLFW/glfw3.h>
#include <light.hpp>

using namespace kr;

Rectangle::Rectangle(btCollisionShape* shape, float mass, ShaderProgram* shader_program
	, glm::vec3 position, glm::mat4 scale
	, glm::mat4 rotate ) :Object(shape, mass, shader_program, position,nullptr, scale, rotate) {
	GLfloat vertices[] = {
         0.5f,  0.5f, 0.0f,  0.0f,  0.0f,  1.0f,  // Top Right
         0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  1.0f,// Bottom Right
        -0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  1.0f,  // Bottom Left
        -0.5f,  0.5f, 0.0f,  0.0f,  0.0f,  1.0f,  // Top Left 
    };
    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3,  // First Triangle
        1, 2, 3   // Second Triangle
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Rectangle::~Rectangle(){
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Rectangle::draw(ShaderProgram* shader_program1) {
	if (shader_program1 == nullptr) {
		shader_program->use();
		set_shaders_parameters(shader_program);
	}
	else {
		shader_program1->use();
		shader_program1->set_uniform_matrix4("model", get_model()*scale*rotate);
		shader_program1->set_uniform_matrix4("lightSpaceMatrix", get_light_space_perspective_matrix());

	}
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Rectangle::set_shaders_parameters(ShaderProgram* shader_program){
	shader_program->set_uniform_vector3f("light.position", get_light_position());
	shader_program->set_uniform_vector3f("viewPos", Camera::get_position());
	shader_program->set_uniform_vector3f("light.ambient", get_light_ambient_color());
	shader_program->set_uniform_vector3f("light.diffuse", get_light_diffuse_color());
	shader_program->set_uniform_vector3f("light.specular", get_light_specular_color());
	//chrome
	shader_program->set_uniform_vector3f("material.ambient", glm::vec3(0.25f, 0.25f, 0.25f));
	shader_program->set_uniform_vector3f("material.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
	shader_program->set_uniform_vector3f("material.specular", glm::vec3(0.774597f, 0.774597, 0.774597));
	shader_program->set_uniform_float("material.shininess", 0.6f);
	glm::mat4 view;
	glm::mat4 projection;
	view = Camera::get_view_matrix();
	projection = Camera::get_projection_matrix();
	shader_program->set_uniform_matrix4("model", get_model()*scale*rotate);
	shader_program->set_uniform_matrix4("view", view);
	shader_program->set_uniform_matrix4("projection", projection);
}

