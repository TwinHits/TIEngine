#include "componentsystems/HoverableComponentSystem.h"

#include "constants/MessageSubscriptions.h"
#include "managers/ComponentSystemsManager.h"
#include "managers/InputManager.h"
#include "managers/MessageManager.h"
#include "managers/ScriptManager.h"
#include "objects/Message.h"
#include "objects/components/HoverableComponent.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

HoverableComponentSystem::HoverableComponentSystem() {
	this->setName(HoverableComponentSystem::HOVERABLE);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(HoverableComponentSystem::HOVERABLE, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(HoverableComponentSystem::ON_HOVER, this);

	this->hoveredMessageSubscription = MessageManager::Instance()->getSubscriptionId("HOVERED");
}

void HoverableComponentSystem::update(const float delta) {
	this->cache.clear();
	this->onHover();
}


HoverableComponent& HoverableComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
	HoverableComponent& component =  this->addComponent(tientity);
	const ScriptTableReader& reader = factory.getReader().getReader(HoverableComponentSystem::HOVERABLE);

	const bool& hoverable = reader.get<bool>(HoverableComponentSystem::HOVERABLE, component.isHoverable());
	component.setHoverable(hoverable);

	const GlobalId& onHoverFunctionId = reader.get<GlobalId>(HoverableComponentSystem::ON_HOVER, component.getOnHoverFunctionId());
	component.setOnHoverFunctionId(onHoverFunctionId);

	return component;
}


HoverableComponent& HoverableComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<HoverableComponent>()) {
		HoverableComponent& hoverableComponent = tientity.addComponent<HoverableComponent>();
		this->components.push_back({ hoverableComponent, tientity });
		return hoverableComponent;
	} else {
		return *tientity.getComponent<HoverableComponent>();
	}
}


bool HoverableComponentSystem::removeComponent(TIEntity& tientity) {
	HoverableComponent* hoverableComponent = tientity.getComponent<HoverableComponent>();
	if (hoverableComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->hoverableComponent == hoverableComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<HoverableComponent>();
	} else {
		return false;
	}
}


void HoverableComponentSystem::setOnHover(TIEntity& tientity, std::function<void(Message&)> onHover) {
	HoverableComponent& hoverableComponent = this->addComponent(tientity);
	hoverableComponent.setOnHoverFunction(onHover);
}


void HoverableComponentSystem::setOnHover(TIEntity& tientity, const GlobalId onHoverFunctionId) {
	HoverableComponent& hoverableComponent = this->addComponent(tientity);
	hoverableComponent.setOnHoverFunctionId(onHoverFunctionId);
}

const std::vector<std::reference_wrapper<TIEntity>>& HoverableComponentSystem::getHoveredTIEntities() {
	return this->cache;
}


void HoverableComponentSystem::onHover() {
    const sf::Vector2f& hoverPosition = InputManager::Instance()->getMouseWindowPosition();
    for (auto& c : this->components) {
        if (c.hoverableComponent.isHoverable()) {
            if (ComponentSystems::doesGlobalBoundsContain(c.tientity, hoverPosition)) {
				if (c.hoverableComponent.getOnHoverFunction()) {
					c.hoverableComponent.getOnHoverFunction()(Message(this->hoveredMessageSubscription, c.tientity.getId(), c.tientity.getId()));
				}
				if (c.hoverableComponent.getOnHoverFunctionId()) {
					ScriptManager::Instance()->runFunction<sol::optional<bool>>(c.hoverableComponent.getOnHoverFunctionId(), c.tientity);
				}
				this->cache.push_back(c.tientity);
            }
        }
    }
}
