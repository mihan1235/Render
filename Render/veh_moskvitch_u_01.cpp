#include<veh_moskvitch_u_01.hpp>

Model* Moskvitch_u_01::model = nullptr;
int Moskvitch_u_01::num = 0;
btCollisionShape* Moskvitch_u_01::shape = nullptr;

btCollisionShape* Moskvitch_u_01::get_shape() {
	return shape;
}

void Moskvitch_u_01::draw(Shader* shader) {
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, value_ptr(get_model()));
	model->Draw(*shader);
}

Moskvitch_u_01::~Moskvitch_u_01() {
	num--;
	if (num == 0) {
		delete shape;
		delete model;
	}
}

Moskvitch_u_01::Moskvitch_u_01(glm::vec3 position) :Object(position) {
	num++;
	mass = 200.0f;
	set_model();
	make_btCollisionShape();
}

void Moskvitch_u_01::set_model() {
	if (model == nullptr) {
		model = new Model("veh_moskvitch_u_01/veh_moskvitch_u_01.obj");
	}
	
}

void Moskvitch_u_01::make_btCollisionShape() {
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
	