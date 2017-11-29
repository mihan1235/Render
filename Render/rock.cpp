#include <rock.hpp>
#include <vector>

using std::vector;

Model* Rock::model = nullptr;
int Rock::num = 0;
btCollisionShape* Rock::shape = nullptr;

btCollisionShape* Rock::get_shape() {
	return shape;
}

void Rock::draw(Shader* shader) {
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, value_ptr(get_model()));
	model->Draw(*shader);
}

void Rock::set_model() {
	if (model == nullptr) {
		model = new Model("rock/rock.blend");
	}
}

void Rock::make_btCollisionShape() {
	vector<btVector3>& points = model->get_physics_vertex_array_ref();
	vector<int>& indices = model->get_physics_indices_array_ref();
	if (shape == nullptr) {
		shape = get_btConvexHullShape(points);
	}
	else {
		printf("Using btConvexHullShape : ");
		printf("Points:[%i]\n",points.size());
		printf("                                   ");
		printf("Indices:[%i]\n", indices.size());
	}
}

Rock::Rock(glm::vec3 position, float mass) :Object(position, mass) {
	num++;
	set_model();
	make_btCollisionShape();
}

Rock::~Rock() {
	num--;
	if (num == 0) {
		delete shape;
		delete model;
	}
}