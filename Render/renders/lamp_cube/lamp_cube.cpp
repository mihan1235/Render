#include <FreeImage.h>
#include <lamp_cube.hpp>
#include <cstdio>
#include <GLFW/glfw3.h>
#include <core.hpp>
#include <light.hpp>


using namespace kr;

LampCube::LampCube(ShaderProgram* shader_program) :Render(shader_program){
	GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };
	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0); // Unbind VAO
}

LampCube::~LampCube(){
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void LampCube::draw(ShaderProgram* shader_program1) {
	if (shader_program1 == nullptr) {
		shader_program->use();
		set_shaders_parameters(shader_program);
	}
	else {
		shader_program1->use();
		glm::mat4 model = glm::translate(glm::mat4(), get_light_position());
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		shader_program1->set_uniform_matrix4("model", model);

	}
	glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void LampCube::set_shaders_parameters(ShaderProgram* shader_program){
	glm::mat4 view = Camera::get_view_matrix();
	glm::mat4 projection = Camera::get_projection_matrix();
	glm::mat4 model = glm::translate(glm::mat4(), get_light_position());
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	shader_program->set_uniform_matrix4("model", model);
	shader_program->set_uniform_matrix4("view", view);
	shader_program->set_uniform_matrix4("projection", projection);
	
}
