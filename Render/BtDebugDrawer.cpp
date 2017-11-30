#include <BtDebugDrawer.hpp>

#include <GL/glew.h>
#include "shader.h"
#include <render.hpp>

BtDebugDrawer::BtDebugDrawer() {
	debug_shader = new Shader("bt_debug_drawer.vert", "bt_debug_drawer.frag");
}

void BtDebugDrawer::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color)
{
	// draws a simple line of pixels between points.
	float vertices[] = {
		from.getX(), from.getY(), from.getZ(), 
		to.getX(), to.getY(), to.getZ(), 
	};
	//printf("[%lf] [%lf] [%lf]\n", from.getX(), from.getY(), from.getZ());

	// use the GL_LINES primitive to draw lines

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// draw our first triangle
	debug_shader->Use();
	glm::mat4 projection = get_projection();
	glm::mat4 view = get_view_matrix();
	debug_shader->setMat4("projection", projection);
	debug_shader->setMat4("view", view);
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_LINES, 0, 2);
	// glBindVertexArray(0); // no need to unbind it every time 

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	//printf("drawing Line\n");
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
	float vertices[] = {
		a.getX(), a.getY(), a.getZ(),
		b.getX(), b.getY(), b.getZ(),
		c.getX(), c.getY(), c.getZ()
	};


	// use the GL_LINES primitive to draw lines

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// draw our first triangle
	debug_shader->Use();
	glm::mat4 projection = get_projection();
	glm::mat4 view = get_view_matrix();
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// glBindVertexArray(0); // no need to unbind it every time 

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	//printf("drawing triangle\n");
}