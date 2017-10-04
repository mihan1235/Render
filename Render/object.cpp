#include <object.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
using std::vector;

Object::Object(vec3 position): IPhysicsObject(position) {
	//this->model_mat = translate(model_mat,position);
}

void Object::draw(Shader* shader) {
	if (model != nullptr) {
		glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, value_ptr(get_model()));
		model->Draw(*shader);
	}
}

void Object::set_model(Model* model) {
	this->model = model;
	// create a vertex cloud defining a square-based pyramid
	/*btVector3 points[5] = { btVector3(-0.5,1,1),
		btVector3(-0.5,1,-1),
		btVector3(-0.5,-1,1),
		btVector3(-0.5,-1,-1),
		btVector3(1,0,0) };*/
	// create our convex hull
	vector<btVector3>& points = model->get_physics_vertex_array_ref();
	printf("Points:[%i]\n", points.size());
	btConvexHullShape* pShape = new btConvexHullShape();
	for (int i = 0; i< points.size(); i++) {
		pShape->addPoint(points[i]);
	}
	// initialize the object as a polyhedron
	//pShape->initializePolyhedralFeatures();
	shape = pShape;
	/*shape = new btBoxShape(btVector3(1, 1, 1));*/
}