#ifndef DEGREEGUIDE_H
#define DEGREEGUIDE_H

#include "objects/tientities/TIEntity.h"

#include <array>
#include <map>

namespace TIE {
	class DegreeGuide : public TIEntity {
		public:
			DegreeGuide();
			~DegreeGuide() {};

			void onWindowSizeChange();
		private:
			void setPosition(TIEntity& degreeGuidePoint, int cardinalPoint, const sf::Vector2i& windowSize);

			std::map<int, TIEntity*> degreeGuidePoints;

			std::array<int, 8> CARDINAL_DEGREES = { 0, 45, 90, 135, 180, 225, 270, 315 };
			int FONT_SIZE = 20;
			float PADDING = 0.95;
	};
}

#endif