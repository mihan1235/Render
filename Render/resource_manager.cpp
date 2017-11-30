
#include <resource_manager.hpp>
#include <render.hpp>

//Objects
#include <cube.hpp>
#include <level.hpp>
#include <zil_131.hpp>
#include <rock.hpp>
#include<trash_benzovoz_gaz_lod.hpp>
#include<veh_moskvitch_u_01.hpp>

using namespace glm;

namespace{
	ResourceManager res_manager;
	BtDebugDrawer* m_pDebugDrawer;
}


ResourceManager::ResourceManager(){

}

void ResourceManager::draw_objects(Shader& shader_program) {
	for (std::vector<Object*>::iterator iter = object_arr.begin(); iter != object_arr.end(); ++iter) {
		// get the object from the iterator
		Object* p_obj = *iter;
		p_obj->draw(&shader_program);
	}
}

void ResourceManager::add_objects_to_physics_manager() {
	////////////////physics manager/////////////////////////
	for (std::vector<Object*>::iterator iter = object_arr.begin(); iter != object_arr.end(); ++iter) {
		// get the object from the iterator
		Object* p_obj = *iter;
		add_rigid_body(p_obj);
	}
	////////////////////////////////////////////////////////
}

void ResourceManager::init_objects() {
	object_arr.push_back(new Level(vec3(0.0f, 0.0f, 0.0f)));
	///////////////////////////////////////////////////
	object_arr.push_back(new Cube(vec3(-4.0f, 13.0f, 0.0), 5.0f));
	object_arr.push_back(new Cube(vec3(-4.0f, 13.5f, -8.0), 5.0f));
	object_arr.push_back(new Cube(vec3(4.0f, 13.0f, 1.0), 5.0f));
	object_arr.push_back(new Cube(vec3(-3.0f, 11.0f, -8.0),5.0f));
	object_arr.push_back(new Cube(vec3(2.5f, 15.2f, 1.5),5.0f));
	object_arr.push_back(new Cube(vec3(-6.0f, 15.0f, 0.0),5.0f));
	object_arr.push_back(new Cube(vec3(6.0f, 15.0f, 0.0), 5.0f));
	object_arr.push_back(new Cube(vec3(7.0f, 15.0f, 1.0), 5.0f));
	object_arr.push_back(new Cube(vec3(7.0f, 13.0f, 4.0), 5.0f));
	object_arr.push_back(new Cube(vec3(8.0f, 13.0f, 5.0), 5.0f));
	object_arr.push_back(new Cube(vec3(9.0f, 13.0f, 3.0), 5.0f));
	object_arr.push_back(new Cube(vec3(10.0f, 13.0f, 4.0), 5.0f));
	///////////////////////////////////////////////
	object_arr.push_back(new Zil_131(vec3(-6.0f, 3.0f, 0.0)));
	///////////////////////////////////////////////////
	//object_arr.push_back(new TrashBenzovozGazLod(vec3(-2.0f, 1.0f, 4.0f)));
	/////////////////////////////////////////////////
	//object_arr.push_back(new Moskvitch_u_01(vec3(-2.0f, 10.2f, -9.0f)));
	///////////////////////////////////////////////
	object_arr.push_back(new Rock(vec3(4.0f, 15.0f, 0.0), 5.0f));
	///////////////////////////////////////////////
	
}

Model& ResourceManager::get_model_ref(const char* name) {
	return *model_map[name];
}


ResourceManager::~ResourceManager(){

	if (object_arr.empty() == false) {
		for (int j = 0; j < object_arr.size(); j++) {
			Object* object = object_arr[j];
			object_arr[j] = nullptr;
			delete object;
		}
	}
	delete m_pDebugDrawer;
}

void init_objects() {
	res_manager.init_objects();
	res_manager.add_objects_to_physics_manager();
}

void draw_objects(Shader& shader) {
	//start_simulation_step();
	res_manager.draw_objects(shader);
}

void set_debug_drawer() {
	m_pDebugDrawer = new BtDebugDrawer();
	set_debug_drawer(m_pDebugDrawer);
}