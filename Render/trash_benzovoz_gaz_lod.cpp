#include<trash_benzovoz_gaz_lod.hpp>

Model* TrashBenzovozGazLod::model = nullptr;
int TrashBenzovozGazLod::num = 0;
btCollisionShape* TrashBenzovozGazLod::shape = nullptr;

btCollisionShape* TrashBenzovozGazLod::get_shape() {
	return shape;
}

void TrashBenzovozGazLod::draw(Shader* shader) {
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, value_ptr(get_model()));
	model->Draw(*shader);
}


TrashBenzovozGazLod::TrashBenzovozGazLod(glm::vec3 position) :Object(position) {
	num++;
	mass = 500.0f;
	set_model();
	make_btCollisionShape();
}

TrashBenzovozGazLod::~TrashBenzovozGazLod() {
	num--;
	if (num == 0) {
		delete shape;
		delete model;
	}
}

void TrashBenzovozGazLod::set_model() {
	if (model == nullptr) {
		model = new  Model("trash_benzovoz_gaz_lod/trash_benzovoz_gaz_lod.obj");
	}
	
}

void TrashBenzovozGazLod::make_btCollisionShape() {
	if (shape == nullptr) {
		shape = get_btConvexHullShape(model->get_physics_vertex_array_ref());
	}
	else {
		printf("Using btConvexHullShape : ");
		printf("Points:[%i]\n", model->get_physics_vertex_array_ref().size());
		printf("                                   ");
		printf("Indices:[%i]\n", model->get_physics_indices_array_ref().size());
	}
	
}