#include<level.hpp>
#include<vector>

using std::vector;

Model* Level::model = nullptr;
int Level::num = 0;
btCollisionShape* Level::shape = nullptr;

btCollisionShape* Level::get_shape() {
	return shape;
}

void Level::draw(Shader* shader) {
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, value_ptr(get_model()));
	model->Draw(*shader);
}

Level::Level(glm::vec3 position):Object(position) {
	num++;
	mass = 0.0f;
	set_model();
	make_btCollisionShape();
}

Level::~Level() {
	num--;
	if (num == 0) {
		delete shape;
		delete model;
	}
}

void Level::set_model() {
	if (model == nullptr) {
		model = new Model("quad/quard.blend");
		//model = new Model("l01_escape/l01_escape.blend");
	}
}

void Level::make_btCollisionShape() {
	vector<btVector3>& points = model->get_physics_vertex_array_ref();
	vector<int>& indices = model->get_physics_indices_array_ref();
	if (shape == nullptr) {
		
		shape = get_btBvhTriangleMeshShape(points, indices);
	}
	else {
		printf("Returning btBvhTriangleMeshShape: ");
		printf("Points:[%i]\n", points.size());
		printf("                                   ");
		printf("Indices:[%i]\n", indices.size());
	}
	
}