#include <object.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <BulletCollision/Gimpact/btGImpactShape.h>

using namespace glm;
using std::vector;

Object::Object(vec3 position) : IPhysicsObject(position) {
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
	//make_btConvexHullShape();
	if (physics) {
		if (level) {
			shape = model->get_btBvhTriangleMeshShape();
		}
		else {
			if (!gimpact) {
				shape = model->get_btConvexHullShape();
			}
			else {
				vector<btVector3>& points = model->get_physics_vertex_array_ref();
				vector<int>& indices = model->get_physics_indices_array_ref();
				printf("Making btGImpactMeshShape: ");
				printf("Points:[%i]\n", points.size());
				printf("                           ");
				printf("Indices:[%i]\n", indices.size());
				btTriangleIndexVertexArray* meshInterface = new btTriangleIndexVertexArray(
					indices.size() / 3,
					&indices[0],
					3 * sizeof(int),
					points.size(),
					(btScalar*)&points[0].x(),
					sizeof(btVector3)
				);
				bool	useQuantizedAabbCompression = true;
				btGImpactMeshShape* trimeshShape = new btGImpactMeshShape(meshInterface);
				trimeshShape->updateBound();
				shape = trimeshShape;
			}

		}

	}
	
}