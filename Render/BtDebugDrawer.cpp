#include <BtDebugDrawer.hpp>

#include <GL/glew.h>
#include "shader.h"
#include <render.hpp>

void BtDebugDrawer::init_gl_draw_line() {

	glGenVertexArrays(1, &VAO_1);
	glGenBuffers(1, &VBO_1);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_1);
	//glBufferData(GL_ARRAY_BUFFER, vertices_1.size() * sizeof(float), &vertices_1[0], GL_STREAM_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO_1 afterwards so other VAO_1 calls won't accidentally modify this VAO_1, but this rarely happens. Modifying other
	// VAO_1s requires a call to glBindVertexArray anyways so we generally don't unbind VAO_1s (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

void BtDebugDrawer::init_gl_draw_triangle() {

	glGenVertexArrays(1, &VAO_2);
	glGenBuffers(1, &VBO_2);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
	//glBufferData(GL_ARRAY_BUFFER, vertices_2.size()*sizeof(float), &vertices_2[0], GL_STREAM_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO_2 as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO_2 afterwards so other VAO_2 calls won't accidentally modify this VAO_2, but this rarely happens. Modifying other
	// VAO_2s requires a call to glBindVertexArray anyways so we generally don't unbind VAO_2s (nor VBO_2s) when it's not directly necessary.
	glBindVertexArray(0);
}

void BtDebugDrawer::draw() {
	
	if (!vertices_1.empty()) {
		// use the GL_LINES primitive to draw lines
		glBindBuffer(GL_ARRAY_BUFFER, VBO_1);
		glBufferData(GL_ARRAY_BUFFER, vertices_1.size() * sizeof(float), &vertices_1[0], GL_STREAM_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// draw our first triangle
		debug_shader->Use();
		glm::mat4 projection = get_projection();
		glm::mat4 view = get_view_matrix();
		debug_shader->setMat4("projection", projection);
		debug_shader->setMat4("view", view);
		glBindVertexArray(VAO_1); // seeing as we only have a single VAO_1 there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_LINES, 0, vertices_1.size());
		// glBindVertexArray(0); // no need to unbind it every time 
		vertices_1.erase(vertices_1.begin(),vertices_1.end());
		//printf("drawing Line\n");
	}

	if (!vertices_2.empty()) {
		// use the GL_LINES primitive to draw lines
		glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
		glBufferData(GL_ARRAY_BUFFER, vertices_2.size()*sizeof(float), &vertices_2[0], GL_STREAM_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// draw our first triangle
		debug_shader->Use();
		glm::mat4 projection = get_projection();
		glm::mat4 view = get_view_matrix();
		glBindVertexArray(VAO_2); // seeing as we only have a single VAO_2 there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, vertices_2.size());
		// glBindVertexArray(0); // no need to unbind it every time 
		vertices_2.erase(vertices_2.begin(), vertices_2.end());
	}
}

BtDebugDrawer::BtDebugDrawer() {
	debug_shader = new Shader("bt_debug_drawer.vert", "bt_debug_drawer.frag");
	init_gl_draw_line();
	init_gl_draw_triangle();
}

BtDebugDrawer::~BtDebugDrawer() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO_1);
	glDeleteBuffers(1, &VBO_1);
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO_2);
	glDeleteBuffers(1, &VBO_2);
}

void BtDebugDrawer::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color)
{
	// draws a simple line of pixels between points.
	vertices_1.push_back(from.getX());
	vertices_1.push_back(from.getY());
	vertices_1.push_back(from.getZ());
	vertices_1.push_back(to.getX());
	vertices_1.push_back(to.getY());
	vertices_1.push_back(to.getZ());
	//printf("[%lf] [%lf] [%lf]\n", from.getX(), from.getY(), from.getZ());

	
}



void BtDebugDrawer::drawContactPoint(const btVector3 &pointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color)

{

	// draws a line between two contact points

	btVector3 const startPoint = pointOnB;

	btVector3 const endPoint = pointOnB + normalOnB * distance;

	drawLine(startPoint, endPoint, color);

}



void BtDebugDrawer::ToggleDebugFlag(int flag) {

	// checks if a flag is set and enables/

	// disables it

	if (m_debugMode & flag)

		// flag is enabled, so disable it

		m_debugMode = m_debugMode & (~flag);

	else

		// flag is disabled, so enable it

		m_debugMode |= flag;

}



void BtDebugDrawer::drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha) {
	// draws a simple line of pixels between points.
	vertices_2.push_back(a.getX());
	vertices_2.push_back(a.getY());
	vertices_2.push_back(a.getZ());
	vertices_2.push_back(b.getX());
	vertices_2.push_back(b.getY());
	vertices_2.push_back(b.getZ());
	vertices_2.push_back(c.getX());
	vertices_2.push_back(c.getY());
	vertices_2.push_back(c.getZ());
	//printf("drawing triangle\n");
}