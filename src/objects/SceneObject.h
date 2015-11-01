#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <SFML/Graphics.hpp>

class SceneObject
{
	public:
		void setDraw(bool b);

		const sf::Sprite& getSprite() const;
		unsigned long getId() const;

		SceneObject(unsigned long id);
		SceneObject(const SceneObject&);
		~SceneObject();
		void operator=(const SceneObject&);
		
	private:
		sf::Sprite sprite;
		bool draw = false;
		unsigned long id;
};

#endif
