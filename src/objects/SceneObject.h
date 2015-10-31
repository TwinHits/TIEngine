#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <SFML/Graphics.hpp>

class SceneObject
{
	public:
		SceneObject(unsigned long id);
		SceneObject(const SceneObject&);
		~SceneObject();
		void operator=(const SceneObject&);

		void setDraw(bool b);

		const sf::Sprite& getSprite();
		unsigned long getId();
		
	private:
		sf::Sprite sprite;
		bool draw = false;
		unsigned long id;
};

#endif
