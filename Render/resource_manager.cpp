
#include <resource_manager.hpp>

ResourceManager::ResourceManager(){

}

void ResourceManager::draw_objects(Shader& shader_program) {
	for (std::vector<Object*>::iterator iter = object_arr.begin(); iter != object_arr.end(); ++iter) {
		// get the object from the iterator
		Object* p_obj = *iter;
		p_obj->draw(&shader_program);
	}
}

//void ResourceManager::add_objects_to_physics_manager(PhysicsManager& physics_manager) {
//	////////////////physics manager/////////////////////////
//	for (std::vector<Object*>::iterator iter = object_arr.begin(); iter != object_arr.end(); ++iter) {
//		// get the object from the iterator
//		Object* p_obj = *iter;
//		physics_manager.add_rigid_body(p_obj);
//	}
//	////////////////////////////////////////////////////////
//}

void ResourceManager::init_objects() {
	init_models();
	glm::mat4 model = glm::mat4();
	///////////////////////////////////////////////////
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	Object* tmp = new Object(model);
	tmp->set_model(model_map["quard"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(-4.0f, 3.5f, -8.0));
	tmp = new Object(model);
	tmp->set_model(model_map["cube"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(4.0f, 3.0f, 1.0));
	tmp = new Object(model);
	tmp->set_model(model_map["cube"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(-3.0f, 1.0f, -8.0));
	tmp = new Object(model);
	tmp->set_model(model_map["cube"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(2.5f, 5.2f, 1.5));
	tmp = new Object(model);
	tmp->set_model(model_map["cube"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(6.5f, 5.0f, -3.0));
	model = glm::rotate(model, 60.0f, glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	tmp = new Object(model);
	tmp->set_model(model_map["cube"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////

	///////////////////////////////////////////////////
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(-6.0f, 0.1f, 0.0));
	//model = glm::rotate(model, 60.0f, glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	//model = glm::scale(model, glm::vec3(1.5));
	tmp = new Object(model);
	tmp->set_model(model_map["zil_131"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(-2.0f, 0.1f, 0.0f));
	//model = glm::rotate(model, 60.0f, glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	//model = glm::scale(model, glm::vec3(1.5));
	tmp = new Object(model);
	tmp->set_model(model_map["trash_benzovoz_gaz_lod"]);
	object_arr.push_back(tmp);
	///////////////////////////////////////////////////
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(-2.0f, 0.2f, 8.0f));
	//model = glm::rotate(model, 60.0f, glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	//model = glm::scale(model, glm::vec3(1.5));
	tmp = new Object(model);
	tmp->set_model(model_map["veh_moskvitch_u_01"]);
	object_arr.push_back(tmp);

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

	if (shader_map.empty() == false) {
		std::map<std::string, Shader*>::iterator it;
		for (it = shader_map.begin(); it != shader_map.end(); ++it) {
			delete it->second;
		}
	}

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
//			glm::scale(glm::mat4(), glm::vec3(2.0f, 2.0f, 2.0f))
//		));
//	object_arr.push_back(
//		new TexturedRectangle(new btBoxShape(btVector3(500, 0, 500)),
//			0.0f,
//			//shader_map["textured_rectangle"],
//			shader_map["cube"],
//			glm::vec3(0.0f, 0.0f, 0.0f),
//			"ston_asfalt_a.dds",
//			glm::scale(glm::mat4(), glm::vec3(500.0f, 500.0f, 500.0f)),
//			glm::rotate(glm::mat4(), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
//		));
//}