#pragma once
#include <shader.h>
#include <model.h>
#include <physics_object.hpp>

class Object :public IPhysicsObject {
	//glm::mat4 model_mat;
public:
	Object(glm::vec3 position);
	virtual void draw(Shader* shader);
	void set_model(Model* model);
	virtual ~Object() {};
private:

protected:
	Model* model = nullptr;
};
