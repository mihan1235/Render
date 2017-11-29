#pragma once

#include <object.hpp>

class Moskvitch_u_01 : public Object {
	static int num;
	static Model* model;
	static btCollisionShape* shape;
public:
	void draw(Shader* shader) override;
	~Moskvitch_u_01();
	Moskvitch_u_01(glm::vec3 position);
	btCollisionShape* get_shape() override;
protected:
	void set_model() override;
	void make_btCollisionShape() override;
};
