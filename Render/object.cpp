#include <object.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Object::Object(glm::mat4 model) {
	this->model_1 = model;
}

void Object::draw(Shader* shader) {
	if (model != nullptr) {
		glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model_1));
		model->Draw(*shader);
	}
}

void Object::set_model(Model* model) {
	this->model = model;
}