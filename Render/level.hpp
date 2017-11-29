#pragma once

#include <object.hpp>

class Level : public Object {
	static int num;
	static Model* model;
	static btCollisionShape* shape;
public:
	Level(glm::vec3 position);
	void draw(Shader* shader) override;
	~Level();
	btCollisionShape* get_shape() override;
protected:
	void set_model() override;
	void make_btCollisionShape() override;
};


