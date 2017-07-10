
#include <resource_manager.hpp>

using namespace kr;

std::map<std::string, GLuint> ResourceManager::texture_map;

ResourceManager::ResourceManager(){

}

void ResourceManager::draw_objects(ShaderProgram* shader_program) {
	for (std::vector<Object*>::iterator iter = object_arr.begin(); iter != object_arr.end(); ++iter) {
		// get the object from the iterator
		Object* p_obj = *iter;
		if (shader_program == nullptr) {
			p_obj->draw();
		}
		else {
			p_obj->draw(shader_program);
		}
	}
	render_map["lamp_cube"]->draw();
}

void ResourceManager::add_objects_to_physics_manager(PhysicsManager& physics_manager) {
	////////////////physics manager/////////////////////////
	for (std::vector<Object*>::iterator iter = object_arr.begin(); iter != object_arr.end(); ++iter) {
		// get the object from the iterator
		PhysicsObject* p_obj = *iter;
		physics_manager.add_rigid_body(p_obj);
	}
	////////////////////////////////////////////////////////
}

void ResourceManager::init_objects() {
	init_textures();
	init_shaders();
	init_render_map();
	init_physics_objects();
}

GLuint ResourceManager::get_texture(const char* name) {
	return texture_map[name];
}


ResourceManager::~ResourceManager(){

	if (object_arr.empty() == false) {
		for (int j = 0; j < object_arr.size(); j++) {
			Object* object = object_arr[j];
			object_arr[j] = nullptr;
			delete object;
		}
	}
	
	if (render_map.empty() == false) {
		std::map<std::string, Render*>::iterator it;
		for (it = render_map.begin(); it != render_map.end(); ++it) {
			delete it->second;
		}
	}

	if (shader_map.empty() == false) {
		std::map<std::string, ShaderProgram*>::iterator it;
		for (it = shader_map.begin(); it != shader_map.end(); ++it) {
			delete it->second;
		}
	}

	if (shader_source_map.empty() == false) {
		std::map<std::string, const GLchar*>::iterator it;
		for (it = shader_source_map.begin(); it != shader_source_map.end(); ++it) {
			delete it->second;
		}
	}
}

void ResourceManager::init_textures() {
	texture_map["wall_yellow_01.dds"] = prepare_texture("data/textures/wall_yellow_01.dds");
	texture_map["grnd_concrete_1.dds"] = prepare_texture("data/textures/grnd_concrete_1.dds");
	texture_map["grnd_grass_mp.dds"] = prepare_texture("data/textures/grnd_grass_mp.dds");
	texture_map["ston_asfalt_hr_iov.dds"] = prepare_texture("data/textures/ston_asfalt_hr_iov.dds");
	texture_map["ston_kirpichi_b.dds"] = prepare_texture("data/textures/ston_kirpichi_b.dds");
	texture_map["ston_asfalt_a.dds"] = prepare_texture("data/textures/ston_asfalt_a.dds");
	texture_map["wall_ceiling_01.dds"] = prepare_texture("data/textures/wall_ceiling_01.dds");
	texture_map["wall_house_red_02.dds"] = prepare_texture("data/textures/wall_house_red_02.dds");
	texture_map["wall_orange_01.dds"] = prepare_texture("data/textures/wall_orange_01.dds");
	texture_map["wood_plank6.dds"] = prepare_texture("data/textures/wood_plank6.dds");
	texture_map["wood_plank7.dds"] = prepare_texture("data/textures/wood_plank7.dds");
	texture_map["wood_razlom_1.dds"] = prepare_texture("data/textures/wood_razlom_1.dds");

	texture_map["depthMap"] = generateAttachmentTexture(true, false);
	texture_map["textureColorbuffer"]= generateAttachmentTexture(false, false);
}

void ResourceManager::init_render_map() {
	render_map["triangle"] = new Triangle(shader_map["triangle"]);
	render_map["lamp_cube"] = new LampCube(shader_map["lamp_cube"]);
}

void ResourceManager::init_shaders() {
	init_shader_sources();
	shader_map["cube"] = new ShaderProgram(shader_source_map["cube_vert"],shader_source_map["cube_frag"]);
	shader_map["rectangle"] = new ShaderProgram(shader_source_map["rectangle_vert"], shader_source_map["rectangle_frag"]);
	shader_map["triangle"] = new ShaderProgram(shader_source_map["triangle_vert"], shader_source_map["triangle_frag"]);
	shader_map["lamp_cube"] = new ShaderProgram(shader_source_map["lamp_cube_vert"], shader_source_map["lamp_cube_frag"]);
	//shader_map["textured_rectangle"] = new ShaderProgram(shader_source_map["textured_rectangle_vert"], shader_source_map["textured_rectangle_frag"]);
}

void ResourceManager::init_shader_sources() {
	shader_source_map["cube_vert"] = read_shader_file("data/shaders/cube/cube.vert");
	shader_source_map["cube_frag"]= read_shader_file("data/shaders/cube/cube.frag");
	shader_source_map["lamp_cube_vert"]= read_shader_file("data/shaders/lamp_cube/lamp_cube_vertex_shader.vert");
	shader_source_map["lamp_cube_frag"]= read_shader_file("data/shaders/lamp_cube/lamp_cube_fragment_shader.frag");
	shader_source_map["rectangle_vert"]= read_shader_file("data/shaders/rectangle/rectangle_vertex_shader.vert");
	shader_source_map["rectangle_frag"]= read_shader_file("data/shaders/rectangle/rectangle_fragment_shader.frag");
	/*shader_source_map["textured_rectangle_vert"]= read_shader_file("data/shaders/textured_rectangle/textured_rectangle.vert");
	shader_source_map["textured_rectangle_frag"] = read_shader_file("data/shaders/textured_rectangle/textured_rectangle.frag");*/
	shader_source_map["triangle_vert"]= read_shader_file("data/shaders/triangle/triangle_vertex_shader.vert");
	shader_source_map["triangle_frag"]= read_shader_file("data/shaders/triangle/triangle_fragment_shader.frag");
}

void ResourceManager::init_physics_objects() {
	//NOTE!! btCollisionShape will be deleted by physics_manager
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(0.0f, 5.0f, 0.0f), 
			"wall_house_red_02.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(10.0f, 25.0f, -55.0f),
			"wall_yellow_01.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(-5.5f, 10.2f, -10.5f),
			"wall_yellow_01.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(-15.8f, 10.0f, -58.3f),
			"wall_orange_01.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(10.4f, 20.4f, -15.5f),
			"wall_yellow_01.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(-5.7f, 15.0f, -35.5f),
			"wall_house_red_02.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(5.3f, 10.0f, -10.5f),
			"wall_yellow_01.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(5.5f, 10.0f, -10.5f), 
			"ston_asfalt_hr_iov.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(0.0f, 10.0f, 0.0f), 
			"wood_plank6.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(1.25f, 20.0f, 0.0f), 
			"wood_razlom_1.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(0.0f, 10.0f, 0.0f),
			"wall_ceiling_01.dds",
			glm::scale(glm::mat4(),	glm::vec3(2.0f, 2.0f, 2.0f))));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(2.25f, 20.0f, 0.0f), 
			"wall_yellow_01.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(3.25f, 22.0f, 0.0f),
			"wall_orange_01.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(1.25f, 24.0f, 0.0f),
			"wall_orange_01.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(4.25f, 26.0f, 0.0f),
			"grnd_grass_mp.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(0.25f, 27.0f, 0.0f),
			"wall_yellow_01.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(2.25f, 28.0f, 0.0f),
			"wall_yellow_01.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(2.25f, 28.0f, 0.0f),
			"wall_orange_01.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(2.25f, 28.0f, 0.0f),
			"wall_yellow_01.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(2.25f, 28.0f, 0.0f),
			"wall_yellow_01.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(2.25f, 28.0f, 0.0f),
			"wall_orange_01.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(2.25f, 28.0f, 0.0f),
			"grnd_concrete_1.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new Cube(new btBoxShape(btVector3(1, 1, 1)),
			1.0f,
			shader_map["cube"],
			glm::vec3(2.25f, 28.0f, 0.0f),
			"wall_yellow_01.dds",
			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
		));
	object_arr.push_back(
		new TexturedRectangle(new btBoxShape(btVector3(500, 0, 500)),
			0.0f,
			//shader_map["textured_rectangle"],
			shader_map["cube"],
			glm::vec3(0.0f, 0.0f, 0.0f),
			"ston_asfalt_a.dds",
			glm::scale(glm::mat4(), glm::vec3(500.0f, 500.0f, 500.0f)),
			glm::rotate(glm::mat4(), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
		));
}