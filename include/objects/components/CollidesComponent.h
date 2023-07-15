#ifndef COLLIDESCOMPONENT_H
#define COLLIDESCOMPONENT_H

#include <SFML/Graphics.hpp>

#include "objects/components/Component.h"
#include "objects/GlobalId.h"

namespace TIE {

class CollidesComponent : public Component {
	public:
		CollidesComponent() {};
		virtual ~CollidesComponent() {};

		void setCollidable(bool drawn);
		bool isCollidable() const;

		void setCollides(bool drawn);
		bool isCollides() const;

		void setPayload(GlobalId id);
		const GlobalId& getPayload() const;

	private:
		bool collidable = false; // I want to know when I hit things
		bool collides = false; // I want to say when I get hit
		GlobalId payload = 0; // The payload id to send on collision
};

}
#endif
