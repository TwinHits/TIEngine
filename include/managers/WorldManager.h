#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include "objects/components/GridComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/entities/GridGuide.h"
#include "objects/entities/TIEntity.h"
#include "objects/factories/TIEntityFactory.h"

namespace TIE {

class WorldManager : public Singleton<WorldManager>, Manager {
	public:
		bool initialize();

		TIEntity* getLevelEntity();
		void setLevelEntity(TIEntity&);

		bool isGridConfigured();
		GridComponent* getGridComponent();

		void showGridGuide(bool);

		TIEntityFactory& registerTIEntity(const std::string& entityName);
		TIEntity* spawnTIEntity(const std::string& entityName);

		WorldManager() {};
		~WorldManager() {};

	private:
		void recalculateGrideGuide(GridComponent*);
		void recalculateScrollBounds(const SpriteComponent&);

		std::map<std::string, TIEntityFactory> tientityDefinitions;

		TIEntity* levelEntity = nullptr;
		GridComponent* gridComponent = nullptr;
		GridGuide* gridGuide = nullptr;
};

}

#endif