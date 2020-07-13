#ifndef GRID_H
#define GRID_H

#include "objects/entities//TIEntity.h"

namespace TIE {

class Grid : public TIEntity {
	public:
		Grid() {};
		~Grid() {};

		const int getWidth() { return this->width; };
		const int getHeight() { return this->height; };

	private:
		int width = 0;
		int height = 0;
};

}
#endif