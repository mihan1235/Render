#include <cube.hpp>
#include <vector>

using std::vector;

Model* Cube::model = nullptr;
int Cube::num = 0;
btCollisionShape* Cube::shape = nullptr;

btCollisionShape* Cube::get_shape() { 
	return shape;
}

void Cube::draw(Shader* shader) {
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, value_ptr(get_model()));
	model->Draw(*shader);
}

void Cube::set_model() {
	if (model == nullptr) {
		model= new Model("cube/cube.obj");
	}
	
}

void Cube::make_btCollisionShape() {
	shape = new btBoxShape(btVector3(1.1, 1.1, 1.1));
	
	/*vector<btVector3>& points = model->get_physics_vertex_array_ref();
	vector<int>& indices = model->get_physics_indices_array_ref();
	if (shape == nullptr) {
		shape = get_btConvexHullShape(points);
	}
	else {
		printf("Using btConvexHullShape : ");
		printf("Points:[%i]\n", points.size());
		printf("                                   ");
		printf("Indices:[%i]\n", indices.size());
	}*/
	
}

Cube::Cube(glm::vec3 position, float mass):Object(position,mass){
	num++;
	set_model();
	make_btCollisionShape();
}

Cube::~Cube() {
	num--;
	if (num == 0) {
		delete shape;
		delete model;
	}
}