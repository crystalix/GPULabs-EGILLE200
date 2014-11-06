#ifndef  Transform_h
#define Transform_h


#include "Component.h"

//header files
#include <iostream>

//header for sdl2 functionality
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
#include "Vertex.h"
#include "Shader.h"

//maths	headers
#include <glm/glm.hpp>
using glm::mat4;
//using glm::mat4;
using glm::vec3;
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Transform : public Component
{
	public:
		Transform();
		//~Transform();
		void update();
		void setPos(vec3 m_Position);
		void setScale(vec3 m_Scale);
		void setRot(vec3 m_Rotation);
		vec3 getPos();
		vec3 getScale();
		vec3 getRot();
		mat4 getModel();
	private:
		vec3 m_Position;
		vec3 m_Scale;
		vec3 m_Rotation;
		mat4 m_Model;



};

#endif