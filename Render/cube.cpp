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
	shader->setMat4("model", get_model());
	model->Draw(*shader);
}

void Cube::set_model() {
	if (model == nullptr) {
		model= new Model("cube/cube.blend");
	}
	
}

void Cube::make_btCollisionShape() {
	shape = new btBoxShape(btVector3(1.0, 1.0, 1.0));
	
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

btTransform Cube::get_default_btTransform() {
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(default_position.x, default_position.y, default_position.z));
	//btQuaternion trans = btQuaternion();
	//trans.setRotation(btVector3(0.0, 0.0, 1.0),btScalar(45.0f));
	//transform.setRotation(trans);
	return transform;
}