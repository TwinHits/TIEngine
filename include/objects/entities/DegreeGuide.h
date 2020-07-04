#ifndef DEGREEGUIDE_H
#define DEGREEGUIDE_H

#include "objects/entities/TIEntity.h"

#include <array>

namespace TIE {
	class DegreeGuide : public TIEntity {
		public:
			DegreeGuide() {};
			~DegreeGuide() {};

			void initialize();
		private:
			std::array<int, 8> CARDINAL_DEGREES = { 0, 45, 90, 135, 180, 225, 270, 315 };
			int FONTSIZE = 20;
			float PADDING = 0.95;
	};
}
#endif