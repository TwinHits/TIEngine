#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <SFML/Graphics.hpp>

class SceneObject
{
	public:
		SceneObject();
		SceneObject(const SceneObject&);
		~SceneObject();
		void operator=(const SceneObject&);

		const sf::Sprite& getSprite();
		void setDraw(bool b);
		
	private:
		sf::Sprite sprite;
		bool draw = false;
};

#endif
