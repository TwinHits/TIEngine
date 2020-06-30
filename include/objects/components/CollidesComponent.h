#ifndef COLLIDESCOMPONENT_H
#define COLLIDESCOMPONENT_H

#include "objects/components/Component.h"

namespace TIE {

class CollidesComponent : public Component {
	public:
		CollidesComponent() {};
		virtual ~CollidesComponent() {};

		void setCollidable(bool drawn);
		bool isCollidable() const;
	private:
		bool collidable = false;
};

}
#endif
