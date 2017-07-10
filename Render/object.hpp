#pragma once
#include <shader.h>
#include <model.h>

class Object {
	glm::mat4 model_1;
public:
	Object(glm::mat4 model);
	virtual void draw(Shader* shader);
	void set_model(Model* model);
	virtual ~Object() {};
private:

protected:
	Model* model = nullptr;
};
