#pragma once

#include <map>
#include <string>
#include <vector>

//objects//
#include <triangle.hpp>
#include <rectangle.hpp>
#include <textured_rectangle.hpp>
#include <cube.hpp>
#include <physics_object.hpp>
#include <lamp_cube.hpp>

#include <physics_manager.hpp>
#include <object.hpp>

namespace kr {
	class ResourceManager {
		std::vector<Object*> object_arr;
		std::map<std::string, Render*> render_map;
		std::map<std::string, ShaderProgram*> shader_map;
		std::map<std::string, const GLchar*> shader_source_map;
		static std::map<std::string, GLuint> texture_map;
	public:
		ResourceManager();
		void draw_objects(ShaderProgram* shader_program=nullptr);
		void add_objects_to_physics_manager(PhysicsManager&);
		void init_objects();
		static GLuint get_texture(const char* name);
		~ResourceManager();
	private:
		void init_textures();
		void init_render_map();
		void init_physics_objects();
		void init_shaders();
		void init_shader_sources();
		ResourceManager(const ResourceManager&);
		ResourceManager& operator=(const ResourceManager&) {};
	protected:
		
	};
}