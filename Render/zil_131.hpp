#pragma once

#include <object.hpp>

class Zil_131 : public Object {
	static int num;
	static Model* model;
	static btCollisionShape* shape;
public:
	void draw(Shader* shader) override;
	Zil_131(glm::vec3 position);
	~Zil_131();
	btCollisionShape* get_shape() override;
protected:
	void set_model() override;
	void make_btCollisionShape() override;
};
