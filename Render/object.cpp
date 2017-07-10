#include <object.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

Object::Object(vec3 position) {
	this->model_mat = translate(model_mat,position);
}

void Object::draw(Shader* shader) {
	if (model != nullptr) {
		glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, value_ptr(model_mat));
		model->Draw(*shader);
	}
}

void Object::set_model(Model* model) {
	this->model = model;
}