#pragma once
// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <FreeImage.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <mesh.h>
#include <shader.h>

#include "btBulletDynamicsCommon.h"

//#include <std::vector.hpp>


GLint TextureFromFile(const char* path,std::string directory, bool gamma = false);


class Model
{
public:
	/*  Model Data */
	std::vector<Texture> textures_loaded;	// Stores all the textures loaded so far, optimization to 
	// make sure textures aren't loaded more than once.
	std::vector<Mesh> meshes;
	std::string directory;
	bool gammaCorrection;

	/*  Functions   */
	// Constructor, expects a filepath to a 3D model.
	Model(std::string const & path, bool gamma = false);
	~Model();
	// Draws the model, and thus all its meshes
	void Draw(Shader shader);
	std::vector<btVector3>& get_physics_vertex_array_ref();
	std::vector<int>& get_physics_indices_array_ref();
	btCollisionShape* get_btConvexHullShape();
	btCollisionShape* get_btConvexTriangleMeshShape();
	btCollisionShape* get_btBvhTriangleMeshShape();

private:
	/*  Functions   */
	// Loads a model with supported ASSIMP extensions from file 
	// and stores the resulting meshes in the meshes vector.
	void loadModel(std::string path);

	// Processes a node in a recursive fashion. Processes each individual mesh
	// located at the node and repeats this process on its children nodes (if any).
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	// Checks all material textures of a given type and loads the textures if they're not loaded yet.
	// The required info is returned as a Texture struct.
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,std::string typeName);
	std::vector<btVector3> physics_vertex_array;
	std::vector<int> physics_indices_array;
	btConvexTriangleMeshShape* ConvexTriangleMeshShape = nullptr;
	btConvexHullShape* ConvexHullShape = nullptr;
	btBvhTriangleMeshShape* BvhTriangleMeshShape = nullptr;
	void delete_shapes();
};