#ifndef Mesh_h
#define Mesh_h

#include "Component.h"

//header for sdl2 functionality
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
#include "Vertex.h"
#include "Shader.h"

class Mesh : public Component
{
	public:
		Mesh();
		void Init();
		void Destroy();
		void copyVertexData(int count, int stride, void** data);
		void copyIndexData(int count, int stride, void** data);
		void Bind();
		int getIndexCount();
		int getVertexCount();

	private:
		GLuint m_VBO;
		GLuint m_EBO;
		GLuint m_VAO;
		int m_VertexCount;
		int m_IndexCount;

};

#endif