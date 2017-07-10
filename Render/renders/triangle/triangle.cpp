#include <triangle.hpp>
#include <camera.hpp>

using namespace kr;

Triangle::Triangle(ShaderProgram* shader_program) : Render(shader_program){
	GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // Left  
         0.5f, -0.5f, 0.0f, // Right 
         0.0f,  0.5f, 0.0f  // Top   
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}

void Triangle::set_shaders_parameters(ShaderProgram* shader_program){
	glm::mat4 view;
	glm::mat4 projection;
	//model = glm::rotate(model, -45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	view = Camera::get_view_matrix();
	projection = Camera::get_projection_matrix();
	glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(1.2f, -10.0f, -20.0f));
	shader_program->set_uniform_matrix4("model", model);
	shader_program->set_uniform_matrix4("view", view);
	shader_program->set_uniform_matrix4("projection", projection);
}

Triangle::~Triangle(){
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Triangle::draw(ShaderProgram* shader_program1) {
	if (shader_program1 == nullptr) {
		shader_program->use();
		set_shaders_parameters(shader_program);
		/*glm::mat4 view = glm::lookAt(glm::vec3(1.2f, -20.0f, -20.0f), glm::vec3(0.0f), glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 1000.0f);
		shader_program->set_uniform_matrix4("view", view);
		shader_program->set_uniform_matrix4("projection", projection);*/
	}
	else {
		shader_program1->use();
		glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(1.2f, -10.0f, -20.0f));
		shader_program1->set_uniform_matrix4("model", model);
	}
	glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}


