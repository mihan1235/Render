#include <physics_object.hpp>
#include <BulletCollision/Gimpact/btGImpactShape.h>

//btCollisionShape* IPhysicsObject::shape = nullptr;
using std::vector;

btCollisionShape* get_btConvexHullShape(vector<btVector3>& points) {
	//vector<btVector3>& points = get_physics_vertex_array_ref();
	/*if (ConvexHullShape != nullptr) {
		printf("Returning btConvexHullShape: ");
		printf("Points:[%i]\n", points.size());
		return ConvexHullShape;
	}*/
	printf("Making btConvexHullShape: ");
	printf("Points:[%i]\n", points.size());
	btConvexHullShape* pShape = new btConvexHullShape();
	for (int i = 0; i < points.size(); i++) {
		pShape->addPoint(points[i]);
	}
	// initialize the object as a polyhedron
	//pShape->initializePolyhedralFeatures();
	/*shape = new btBoxShape(btVector3(1, 1, 1));*/
	return pShape;
}

btCollisionShape* get_btConvexTriangleMeshShape(vector<btVector3>& points, vector<int>& indices) {
	/*vector<btVector3>& points = get_physics_vertex_array_ref();
	vector<int>& indices = get_physics_indices_array_ref();*/
	/*if (ConvexTriangleMeshShape != nullptr) {
		printf("Returning btConvexTriangleMeshShape: ");
		printf("Points:[%i]\n", points.size());
		printf("                                   ");
		printf("Indices:[%i]\n", indices.size());
		return ConvexTriangleMeshShape;
	}*/
	//btTriangleIndexVertexArray* meshInterface = new btTriangleIndexVertexArray();
	//btIndexedMesh part;
	printf("Making btConvexTriangleMeshShape: ");
	printf("Points:[%i]\n", points.size());
	printf("                                   ");
	printf("Indices:[%i]\n", indices.size());
	/*{
	vector<btVector3>& points_vector = model->get_physics_vertex_array_ref();
	printf("points: [%i]\n", points_vector.size());

	points.reserve(points_vector.size() * 3);
	for (int i = 0; i < points_vector.size(); i++) {
	points.push_back(points_vector[i].getX());
	points.push_back(points_vector[i].getY());
	points.push_back(points_vector[i].getZ());
	}
	}*/

	btTriangleIndexVertexArray* meshInterface = new btTriangleIndexVertexArray(
		indices.size() / 3,
		&indices[0],
		3 * sizeof(int),
		points.size(),
		(btScalar*)&points[0].x(),
		sizeof(btVector3)
	);

	//btTriangleIndexVertexArray* meshInterface = new btTriangleIndexVertexArray();
	//btIndexedMesh mesh;

	//const int stride = 3; // For vertex indices and vertices, see BVG.cpp for explanation
	//mesh.m_indexType = PHY_INTEGER;
	//mesh.m_numTriangles = indices.size();
	//mesh.m_triangleIndexStride = stride * sizeof(int);
	//mesh.m_triangleIndexBase = new unsigned char[sizeof(int) * indices.size()];// Allocate memory for the mesh

	//mesh.m_vertexType = PHY_FLOAT;
	//mesh.m_numVertices = points.size() / stride;
	//mesh.m_vertexStride = stride * sizeof(float);
	//mesh.m_vertexBase = new unsigned char[sizeof(btScalar) * points.size()];// Allocate memory for the mesh

	// // copy indices into mesh
	//int* indicesP = static_cast<int*>((void*)(mesh.m_triangleIndexBase));
	//for (int i = 0; i < indices.size(); ++i) {
	//	indicesP[i] = indices.at(i);
	//}
	//// copy vertices into mesh
	//btScalar* vertexData = static_cast<btScalar*>((void*)(mesh.m_vertexBase));
	//for (int i = 0; i < points.size(); ++i) {
	//	vertexData[i] = points.at(i);
	//}
	//meshInterface->addIndexedMesh(mesh);
	bool	useQuantizedAabbCompression = true;
	btConvexTriangleMeshShape* trimeshShape = new btConvexTriangleMeshShape(meshInterface, useQuantizedAabbCompression);
	//ConvexTriangleMeshShape = trimeshShape;

	/*btGImpactMeshShape
	#include <BulletCollision/Gimpact/btGImpactShape.h>*/
	return trimeshShape;
}

btCollisionShape* get_btBvhTriangleMeshShape(vector<btVector3>& points, vector<int>& indices) {
	/*vector<int>& indices = get_physics_indices_array_ref();
	vector<btVector3>& points = get_physics_vertex_array_ref();*/
	/*if (BvhTriangleMeshShape != nullptr) {
		printf("Returning btBvhTriangleMeshShape: ");
		printf("Points:[%i]\n", points.size());
		printf("                                   ");
		printf("Indices:[%i]\n", indices.size());
		return BvhTriangleMeshShape;
	}*/
	//btTriangleIndexVertexArray* meshInterface = new btTriangleIndexVertexArray();
	//btIndexedMesh part;

	printf("Making btBvhTriangleMeshShape: ");
	printf("Points:[%i]\n", points.size());
	printf("                                   ");
	printf("Indices:[%i]\n", indices.size());
	/*{
	vector<btVector3>& points_vector = model->get_physics_vertex_array_ref();
	printf("points: [%i]\n", points_vector.size());

	points.reserve(points_vector.size() * 3);
	for (int i = 0; i < points_vector.size(); i++) {
	points.push_back(points_vector[i].getX());
	points.push_back(points_vector[i].getY());
	points.push_back(points_vector[i].getZ());
	}
	}*/

	btTriangleIndexVertexArray* meshInterface = new btTriangleIndexVertexArray(
		indices.size() / 3,
		&indices[0],
		3 * sizeof(int),
		points.size(),
		(btScalar*)&points[0].x(),
		sizeof(btVector3)
	);

	//btTriangleIndexVertexArray* meshInterface = new btTriangleIndexVertexArray();
	//btIndexedMesh mesh;

	//const int stride = 3; // For vertex indices and vertices, see BVG.cpp for explanation
	//mesh.m_indexType = PHY_INTEGER;
	//mesh.m_numTriangles = indices.size();
	//mesh.m_triangleIndexStride = stride * sizeof(int);
	//mesh.m_triangleIndexBase = new unsigned char[sizeof(int) * indices.size()];// Allocate memory for the mesh

	//mesh.m_vertexType = PHY_FLOAT;
	//mesh.m_numVertices = points.size() / stride;
	//mesh.m_vertexStride = stride * sizeof(float);
	//mesh.m_vertexBase = new unsigned char[sizeof(btScalar) * points.size()];// Allocate memory for the mesh

	// // copy indices into mesh
	//int* indicesP = static_cast<int*>((void*)(mesh.m_triangleIndexBase));
	//for (int i = 0; i < indices.size(); ++i) {
	//	indicesP[i] = indices.at(i);
	//}
	//// copy vertices into mesh
	//btScalar* vertexData = static_cast<btScalar*>((void*)(mesh.m_vertexBase));
	//for (int i = 0; i < points.size(); ++i) {
	//	vertexData[i] = points.at(i);
	//}
	//meshInterface->addIndexedMesh(mesh);
	bool	useQuantizedAabbCompression = true;
	btBvhTriangleMeshShape* trimeshShape = new btBvhTriangleMeshShape(meshInterface, useQuantizedAabbCompression);
	//BvhTriangleMeshShape = trimeshShape;

	/*btGImpactMeshShape
	#include <BulletCollision/Gimpact/btGImpactShape.h>*/
	return trimeshShape;
}

btCollisionShape* get_btGImpactMeshShape(std::vector<btVector3>& points, std::vector<int>& indices) {
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
	return trimeshShape;
}

IPhysicsObject::IPhysicsObject(glm::vec3 position,float mass){
	this->mass=mass;
	this->default_position = position;
};

glm::mat4 IPhysicsObject::get_model() {
    return glm::translate(glm::mat4(), position()) * glm::mat4_cast(orientation());
}

glm::vec3 IPhysicsObject::position() {
    btTransform transform;
    body->getMotionState()->getWorldTransform(transform);
    return {transform.getOrigin().getX(), transform.getOrigin().getY(), transform.getOrigin().getZ()};
}

glm::quat IPhysicsObject::orientation() {
    btTransform transform;
    body->getMotionState()->getWorldTransform(transform);
    return glm::angleAxis(transform.getRotation().getAngle(),
						 glm::normalize(glm::vec3(
                         transform.getRotation().getAxis().getX(),
                         transform.getRotation().getAxis().getY(),
                         transform.getRotation().getAxis().getZ())));
}

//btCollisionShape* IPhysicsObject::get_shape() { 
//	return shape;
//}

btRigidBody* IPhysicsObject::get_rigid_body() { 
	return body;
}

void IPhysicsObject::set_rigid_body(btRigidBody* body) { 
	this->body=body;
}

float IPhysicsObject::get_mass(){
	return mass;
}

void IPhysicsObject::set_mass(float mass){
	this->mass=mass;
}

IPhysicsObject::~IPhysicsObject(){
	
};

glm::vec3 IPhysicsObject::get_default_position(){
	return default_position;
}

btTransform IPhysicsObject::get_default_btTransform() {
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(default_position.x, default_position.y, default_position.z));
	//btQuaternion trans = btQuaternion();
	//trans.setRotation(btVector3(0.0, 0.0, 1.0),btScalar(45.0f));
	//transform.setRotation(trans);
	return transform;
}
