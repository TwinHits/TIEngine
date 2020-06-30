#include <SFML/Graphics.hpp>

#include "managers/componentsystems/MovesComponentSystem.h" 

#include "objects/components/MovesComponent.h"
#include "objects/entities/TIEntity.h"

using namespace TIE;

void MovesComponentSystem::execute(TIEntity& entity) {
	MovesComponent* movesComponent = entity.getComponent<MovesComponent>();
	if (movesComponent != nullptr) {

	}
}
