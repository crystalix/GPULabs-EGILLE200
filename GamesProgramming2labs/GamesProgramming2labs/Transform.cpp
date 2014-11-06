#include "Transform.h"

Transform::Transform()
{

}

void Transform::update()
{
	mat4 translate = glm::translate(translate, m_Position);
	mat4 scale =glm::scale(scale, m_Scale);

	mat4 rotationX = glm::rotate(rotationX,m_Rotation.x,vec3(1.0f,0.0f,0.0f));
	mat4 rotationY = glm::rotate(rotationY,m_Rotation.y,vec3(0.0f,1.0f,0.0f));
	mat4 rotationZ = glm::rotate(rotationZ,m_Rotation.z,vec3(0.0f,0.0f,1.0f));
	mat4 rotation = rotationX*rotationY*rotationZ;

	m_Model = translate*rotation*scale;
}

void Transform::setPos(vec3 Position)
{
	m_Position = Position; 
}

void Transform::setScale(vec3 Scale)
{
	m_Scale = Scale;
}

void Transform::setRot(vec3 Rotation)
{
	m_Rotation = Rotation;
}

vec3 Transform::getPos()
{
	return m_Position;
}

vec3 Transform::getScale()
{
	return m_Scale;
}

vec3 Transform::getRot()
{
	return m_Rotation;
}

mat4 Transform::getModel()
{
	return m_Model;
}