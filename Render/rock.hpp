#pragma once

#include <object.hpp>

class Rock : public Object {
	static int num;
	static Model* model;
	static btCollisionShape* shape;
public:
	Rock(glm::vec3 position, float mass = 0.0f);
	void draw(Shader* shader) override;
	~Rock();
	btCollisionShape* get_shape() override;
protected:
	void set_model() override;
	void make_btCollisionShape() override;
};