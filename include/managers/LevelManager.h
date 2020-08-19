#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include "objects/components/GridComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/GridGuide.h"
#include "objects/entities/TIEntity.h"

namespace TIE {

class LevelManager : public Singleton<LevelManager>, Manager {
	public:
		bool initialize();

		bool isGridConfigured();

		TIEntity* getLevelEntity();
		void setLevelEntity(TIEntity&);

		GridComponent* getGridComponent();

		void showGridGuide(bool);

		LevelManager() {};
		~LevelManager() {};

	private:
		void recalculateGrideGuide(GridComponent*);
		void recalculateScrollBounds(const SpriteComponent&);

		TIEntity* levelEntity = nullptr;
		GridComponent* gridComponent = nullptr;
		GridGuide* gridGuide = nullptr;
};

}

#endif