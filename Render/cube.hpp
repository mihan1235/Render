#pragma once

#include <object.hpp>

class Cube : public Object {
	static int num;
	static Model* model;
	static btCollisionShape* shape;
public:
	void draw(Shader* shader) override;
	~Cube();
	Cube(glm::vec3 position, float mass = 0.0f);
	btCollisionShape* get_shape() override;
protected:
	void set_model() override;
	void make_btCollisionShape() override;
};