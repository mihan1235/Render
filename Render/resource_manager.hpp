#pragma once

#include <map>
#include <string>
#include <vector>

#include <physics_object.hpp>

#include <physics_manager.hpp>
#include <object.hpp>


class ResourceManager {
	std::vector<Object*> object_arr;
	//std::map<std::string, Shader*> shader_map;
	std::map<std::string, Model* > model_map;
public:
	ResourceManager();
	void draw_objects(Shader& shader);
	void add_objects_to_physics_manager();
	void init_objects();
	~ResourceManager();
	/*Shader& get_shader_ref(const char* name);*/
	Model& get_model_ref(const char* name);
private:
	//void init_models();
	ResourceManager(const ResourceManager&);
	ResourceManager& operator=(const ResourceManager&) {};
protected:
		
};

void init_objects();
void draw_objects(Shader& shader);
