#include <object.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace glm;

Object::~Object() {
}

Object::Object(vec3 position, float mass) : IPhysicsObject(position, mass) {
}


