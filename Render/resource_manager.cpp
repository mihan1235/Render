
#include <resource_manager.hpp>
#include <render.hpp>

using namespace glm;

namespace{
	ResourceManager res_manager;
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
	init_models();
	///////////////////////////////////////////////////
	Object* tmp = new Object(vec3(0.0f, 0.0f, 0.0f));
	tmp->level = true;
	tmp->set_model(model_map["quard"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////
	tmp = new Object(vec3(-4.0f, 13.5f, -8.0));
	tmp->set_mass(5.0f);
	tmp->set_model(model_map["cube"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////
	tmp = new Object(vec3(4.0f, 13.0f, 1.0));
	tmp->set_mass(5.0f);
	tmp->set_model(model_map["cube"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////
	tmp = new Object(vec3(-3.0f, 11.0f, -8.0));
	tmp->set_mass(5.0f);
	tmp->set_model(model_map["cube"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////
	tmp = new Object(vec3(2.5f, 15.2f, 1.5));
	tmp->set_mass(5.0f);
	tmp->set_model(model_map["cube"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////
	tmp = new Object(vec3(-6.0f, 15.0f, 0.0));
	tmp->set_mass(5.0f);
	tmp->set_model(model_map["cube"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////

	///////////////////////////////////////////////////
	tmp = new Object(vec3(-6.0f, 0.10f, 0.0));
	tmp->set_mass(500.0f);
	tmp->set_model(model_map["zil_131"]);
	object_arr.push_back(tmp);
	/////////////////////////////////////////////////////
	tmp = new Object(vec3(-2.0f, 1.0f, 4.0f));
	tmp->set_mass(500.0f);
	tmp->set_model(model_map["trash_benzovoz_gaz_lod"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////
	//tmp = new Object(vec3(-2.0f, 0.2f, 8.0f));
	tmp = new Object(vec3(-2.0f, 10.2f, -9.0f));
	tmp->set_mass(200.0f);
	tmp->set_model(model_map["veh_moskvitch_u_01"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////
	tmp = new Object(vec3(6.0f, 15.0f, 0.0));
	tmp->set_mass(5.0f);
	tmp->set_model(model_map["cube"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////
	///////////////////////////////////////////////////
	tmp = new Object(vec3(4.0f, 15.0f, 0.0));
	tmp->set_mass(5.0f);
	tmp->set_model(model_map["cube"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////
	///////////////////////////////////////////////////
	tmp = new Object(vec3(7.0f, 15.0f, 1.0));
	tmp->set_mass(5.0f);
	tmp->set_model(model_map["cube"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////
	///////////////////////////////////////////////////
	tmp = new Object(vec3(7.0f, 13.0f, 4.0));
	tmp->set_mass(5.0f);
	tmp->set_model(model_map["cube"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////
	///////////////////////////////////////////////////
	tmp = new Object(vec3(8.0f, 13.0f, 5.0));
	tmp->set_mass(5.0f);
	tmp->set_model(model_map["cube"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////
	///////////////////////////////////////////////////
	tmp = new Object(vec3(9.0f, 13.0f, 3.0));
	tmp->set_mass(5.0f);
	tmp->set_model(model_map["cube"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////
	///////////////////////////////////////////////////
	tmp = new Object(vec3(10.0f, 13.0f, 4.0));
	tmp->set_mass(5.0f);
	tmp->set_model(model_map["cube"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////

}

void ResourceManager::init_models(){
    model_map["zil_131"]= new Model("zil_131/zil_131.obj");
	model_map["cube"] = new Model("cube/cube.obj");
	model_map["quard"]= new Model("quad/quard.blend");
	model_map["trash_benzovoz_gaz_lod"]=new  Model("trash_benzovoz_gaz_lod/trash_benzovoz_gaz_lod.obj");
	model_map["veh_moskvitch_u_01"] = new Model("veh_moskvitch_u_01/veh_moskvitch_u_01.obj");

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

	/*if (shader_map.empty() == false) {
		std::map<std::string, Shader*>::iterator it;
		for (it = shader_map.begin(); it != shader_map.end(); ++it) {
			delete it->second;
		}
	}*/

	if (model_map.empty() == false) {
		std::map<std::string, Model*>::iterator it;
		for (it = model_map.begin(); it != model_map.end(); ++it) {
			delete it->second;
		}
	}
}



//void ResourceManager::init_physics_objects() {
//	//NOTE!! btCollisionShape will be deleted by physics_manager
//	object_arr.push_back(
//		new Cube(new btBoxShape(btVector3(1, 1, 1)),
//			1.0f,
//			shader_map["cube"],
//			glm::vec3(0.0f, 5.0f, 0.0f), 
//			"wall_house_red_02.dds",
//			glm::scale(glm::mat4(),vec3(2.0f, 2.0f, 2.0f))
//		));
//	object_arr.push_back(
//		new TexturedRectangle(new btBoxShape(btVector3(500, 0, 500)),
//			0.0f,
//			//shader_map["textured_rectangle"],
//			shader_map["cube"],
//			glm::vec3(0.0f, 0.0f, 0.0f),
//			"ston_asfalt_a.dds",
//			glm::scale(glm::mat4(),vec3(500.0f, 500.0f, 500.0f)),
//			glm::rotate(glm::mat4(),radians(-90.0f),vec3(1.0f, 0.0f, 0.0f))
//		));
//}

void init_objects() {
	res_manager.init_objects();
	res_manager.add_objects_to_physics_manager();
}

void draw_objects(Shader& shader) {
	start_simulation_step();
	res_manager.draw_objects(shader);
}