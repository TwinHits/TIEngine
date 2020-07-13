#ifndef GRIDCOMPONENT_H
#define GRIDCOMPONENT_H

#include "objects/components/Component.h"

#include <functional>

#include "objects/entities/Grid.h"

namespace TIE {

class GridComponent : public Component {
	public:
		GridComponent(const Grid& grid);
		~GridComponent() {};

	private:
		const Grid& grid;
};

}

#endif
