#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include "objects/SceneLayer.h"
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
		void setLevelEntity(TIEntityFactory&);

		bool isGridConfigured();
		GridComponent* getGridComponent();

		void showGridGuide(bool);

		TIEntity& registerTIEntity(TIEntity&);
		TIEntity* getTIEntityById(GlobalId);
		TIEntityFactory& saveTIEntityFactory(const std::string&, TIEntityFactory&);
		TIEntityFactory* getTIEntityFactory(const std::string&);


		WorldManager() {};
		~WorldManager() {};

	private:
		void recalculateGrideGuide(GridComponent*);
		void recalculateScrollBounds(const SpriteComponent&);

		std::map<std::string, std::unique_ptr<TIEntityFactory> > factories;
		std::map<GlobalId, TIEntity*> tientities;

		SceneLayer* worldLayer = nullptr;
		TIEntity* levelEntity = nullptr;
		GridComponent* gridComponent = nullptr;
		GridGuide* gridGuide = nullptr;
};

}

#endif