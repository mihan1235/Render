#include<zil_131.hpp>

Model* Zil_131::model = nullptr;
int Zil_131::num = 0;
btCollisionShape* Zil_131::shape = nullptr;

btCollisionShape* Zil_131::get_shape() {
	return shape;
}

void Zil_131::draw(Shader* shader) {
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, value_ptr(get_model()));
	model->Draw(*shader);
}

Zil_131::Zil_131(glm::vec3 position) :Object(position) {
	num++;
	mass = 500.0f;
	set_model();
	make_btCollisionShape();
}

Zil_131::~Zil_131() {
	num--;
	if (num == 0) {
		delete shape;
		delete model;
	}
}

void Zil_131::set_model() {
	if (model == nullptr) {
		model = new Model("zil_131/zil_131.obj");
	}
	
}

void Zil_131::make_btCollisionShape() {
	
	if (shape == nullptr) {
		shape = get_btGImpactMeshShape(model->get_physics_vertex_array_ref(), model->get_physics_indices_array_ref());
		// = get_btConvexTriangleMeshShape(model->get_physics_vertex_array_ref(), model->get_physics_indices_array_ref());
	}
	else {
		printf("Using btGImpactMeshShape: ");
		printf("Points:[%i]\n", model->get_physics_vertex_array_ref().size());
		printf("                                   ");
		printf("Indices:[%i]\n", model->get_physics_indices_array_ref().size());
	}
}