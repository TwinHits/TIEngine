#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include <map>
#include <memory>

#include "objects/components/GridComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/tientities/engine/GridGuide.h"
#include "objects/tientities/common/SceneLayer.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "objects/factories/ai/FiniteStateMachineFactory.h"
#include "objects/factories/ai/BehaviorTreeNodeFactory.h"

namespace TIE {

class WorldManager : public Singleton<WorldManager>, public Manager {
	public:
		void initialize();

		TIEntity* getLevelEntity();
		void setLevelEntity(TIEntityFactory&);

		bool isGridConfigured();
		GridComponent* getGridComponent();

		void showGridGuide(bool);

		TIEntity& registerTIEntity(TIEntity&);
		void deregisterTIEntity(TIEntity&);
		TIEntity* getTIEntityById(GlobalId);

		TIEntityFactory& saveTIEntityFactory(const std::string&, TIEntityFactory&);
		TIEntityFactory* getTIEntityFactory(const std::string&);

		FiniteStateMachineFactory& saveFiniteStateMachineFactory(GlobalId, FiniteStateMachineFactory&);
		FiniteStateMachineFactory* getFiniteStateMachineFactory(GlobalId);

		BehaviorTreeNodeFactory& saveBehaviorTreeNodeFactory(GlobalId, BehaviorTreeNodeFactory&);
		BehaviorTreeNodeFactory* getBehaviorTreeNodeFactory(GlobalId);

		WorldManager() {};
		~WorldManager() {};

	private:
		void recalculateGrideGuide(GridComponent*);
		void recalculateScrollBounds(const SpriteComponent&);

		std::map<std::string, std::unique_ptr<TIEntityFactory> > tiEntityFactories;
		std::map<GlobalId, std::unique_ptr<FiniteStateMachineFactory> > finiteStateMachineFactories;
		std::map<GlobalId, std::unique_ptr<BehaviorTreeNodeFactory> > behaviorTreeNodeFactories;
		std::map<GlobalId, TIEntity*> tientities;

		SceneLayer* worldLayer = nullptr;
		TIEntity* levelEntity = nullptr;
		GridComponent* gridComponent = nullptr;
		GridGuide* gridGuide = nullptr;
};

}

#endif