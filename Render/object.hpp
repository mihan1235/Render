#pragma once
#include <shader.h>
#include <model.h>
#include <physics_object.hpp>

class Object :public IPhysicsObject {
	static int num;
public:
	Object(glm::vec3 position, float mass = 0.0f);
	virtual void draw(Shader* shader)=0;
	virtual ~Object();
private:
protected:
	virtual void set_model() = 0;
	virtual void make_btCollisionShape() = 0;
};
