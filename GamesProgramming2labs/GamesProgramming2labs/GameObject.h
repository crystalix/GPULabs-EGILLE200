#ifndef  GameObject_h
#define GameObject_h

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Component.h"

class GameObject
{
	public:
		GameObject();
		void init();
		void update();
		void render();
		void destroy();
		const std::string& getName();
		void setName(const std::string& name);
		void addComponent(Component(Component * component));

	protected:
	private:
		std::string m_Name;
		std::vector<Component*> m_Components;
};


#endif
