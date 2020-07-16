#ifndef TIENTITYFACTORY_H
#define TIENTITYFACTORY_H

#include <string>

#include "objects/entities/TIEntity.h" 

namespace TIE {

class TIEntityFactory {
	public:
		TIEntity& build();

		TIEntityFactory& setParent(TIEntity*);
		TIEntityFactory& setName(std::string);

		TIEntityFactory& setDrawn(const bool);
		TIEntityFactory& setTexture(const std::string&);
		TIEntityFactory& setText(const std::string&);

		TIEntityFactory& setSpeed(const float);
		TIEntityFactory& setDirection(const float);

		TIEntityFactory& setSelectable(const bool);

		TIEntityFactory() {};
		~TIEntityFactory() {};

		static const std::string DRAWN;
		static const std::string TEXTURE;
		static const std::string TEXT;

		static const std::string MOVES;
		static const std::string SPEED;
		static const std::string DIRECTION;

		static const std::string SELECTABLE;
	private:
		TIEntity* parent = nullptr;
		std::string name = "";

		bool hasSprite = false;
		bool hasText = false;
		bool isDrawn = false;
		std::string texture = "";
		std::string text = "";

		bool hasMoves = false;
		float speed = 0;
		float direction = 0;

		bool hasSelectable = false;
		bool isSelectable = false;
};

}
#endif
