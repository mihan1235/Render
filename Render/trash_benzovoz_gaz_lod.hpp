#pragma once

#include <object.hpp>

class TrashBenzovozGazLod : public Object {
	static int num;
	static Model* model;
	static btCollisionShape* shape;
public:
	void draw(Shader* shader) override;
	~TrashBenzovozGazLod();
	TrashBenzovozGazLod(glm::vec3 position);
	btCollisionShape* get_shape() override;
protected:
	void set_model() override;
	void make_btCollisionShape() override;
};
