#ifndef GRIDMANAGER_H
#define GRIDMANAGER_H

#include "managers/Manager.h"
#include "templates/Singleton.h"

#include "objects/components/GridComponent.h"
#include "objects/entities/TIEntity.h"

namespace TIE {

class GridManager : public Singleton<GridManager>, Manager {
	public:
		bool initialize();

		bool isGridConfigured();

		TIEntity* getGridEntity();
		void setGridEntity(TIEntity&);

		GridComponent* getGridComponent();

		GridManager() {};
		~GridManager() {};

	private:
		TIEntity* gridEntity = nullptr;
		GridComponent* gridComponent = nullptr;
};

}

#endif