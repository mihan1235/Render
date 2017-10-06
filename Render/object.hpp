#pragma once
#include <shader.h>
#include <model.h>
#include <physics_object.hpp>

class Object :public IPhysicsObject {
	//glm::mat4 model_mat;
	
	
public:
	bool level = false;
	bool gimpact = false;
	bool physics = true;
	Object(glm::vec3 position);
	virtual void draw(Shader* shader);
	void set_model(Model* model);
	virtual ~Object() {};
private:
	/*void make_btConvexHullShape() override;
	void make_btConvexTriangleMeshShape() override;*/
protected:
	Model* model = nullptr;
};
