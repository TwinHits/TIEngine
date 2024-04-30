#include "componentsystems/ClickableComponentSystem.h" 

#include "componentsystems/MessagesComponentSystem.h"
#include "managers/ComponentSystemsManager.h"
#include "managers/InputManager.h"
#include "managers/MessageManager.h"
#include "managers/ScriptManager.h"
#include "objects/Message.h"
#include "objects/components/ClickableComponent.h"
#include "objects/constants/MessageSubscriptions.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "objects/tientities/TIEntity.h"

using namespace TIE;

ClickableComponentSystem::ClickableComponentSystem() {
	this->setName(ClickableComponentSystem::CLICKABLE);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(ClickableComponentSystem::CLICKABLE, this);
	ComponentSystemsManager::Instance()->registerComponentPropertyKey(ClickableComponentSystem::ON_CLICK, this);

	this->clickedMessageSubscription = MessageManager::Instance()->getSubscriptionId("Clicked");

	MessageManager::Instance()->subscribe(MessageSubscriptions::MOUSE_BUTTON_PRESSED, std::bind(&ClickableComponentSystem::onClick, this));
}

void ClickableComponentSystem::update(const float delta) {

}


ClickableComponent& ClickableComponentSystem::addComponent(const TIEntityFactory& factory, TIEntity& tientity) {
	ClickableComponent& component =  this->addComponent(tientity);
	const ScriptTableReader& reader = factory.getReader().getReader(ClickableComponentSystem::CLICKABLE);

	const bool& clickable = reader.get<bool>(ClickableComponentSystem::CLICKABLE, component.isClickable());
	component.setClickable(clickable);

	const GlobalId& onClickFunctionId = reader.get<GlobalId>(ClickableComponentSystem::ON_CLICK, component.getOnClickFunctionId());
	component.setOnClickFunctionId(onClickFunctionId);

	return component;
}


ClickableComponent& ClickableComponentSystem::addComponent(TIEntity& tientity) {
	if (!tientity.hasComponent<ClickableComponent>()) {
		ClickableComponent& clickableComponent = tientity.addComponent<ClickableComponent>();
		MessagesComponent& messagesComponent = MessagesComponentSystem::Instance()->addComponent(tientity);
		this->components.push_back({ clickableComponent, messagesComponent, tientity });
		return clickableComponent;
	} else {
		return *tientity.getComponent<ClickableComponent>();
	}
}


bool ClickableComponentSystem::removeComponent(TIEntity& tientity) {
	ClickableComponent* clickableComponent = tientity.getComponent<ClickableComponent>();
	if (clickableComponent != nullptr) {
		for (auto i = this->components.begin(); i != this->components.end(); ++i) {
			if (&i->clickableComponent == clickableComponent) {
				this->components.erase(i);
				break;
			}
		}
		return tientity.removeComponent<ClickableComponent>();
	} else {
		return false;
	}
}


void ClickableComponentSystem::setOnClick(TIEntity& tientity, std::function<void(Message&)> onClick) {
	ClickableComponent& clickableComponent = this->addComponent(tientity);
	clickableComponent.setOnClickFunction(onClick);
	MessagesComponentSystem::Instance()->subscribe(tientity, this->clickedMessageSubscription, onClick);
}


void ClickableComponentSystem::setOnClick(TIEntity& tientity, const GlobalId onClickFunctionId) {
	ClickableComponent& clickableComponent = this->addComponent(tientity);
	clickableComponent.setOnClickFunctionId(onClickFunctionId);
}


void ClickableComponentSystem::onClick() {
    const sf::Vector2f& clickPosition = InputManager::Instance()->getMouseWindowPosition();
    for (auto& c : this->components) {
        if (c.clickableComponent.isClickable()) {
            if (ComponentSystems::doesGlobalBoundsContain(c.tientity, clickPosition)) {
				if (c.clickableComponent.getOnClickFunction()) {
					MessagesComponentSystem::Instance()->sendMessage(Message(this->clickedMessageSubscription, c.tientity.getId(), c.tientity.getId()));
				}
				if (c.clickableComponent.getOnClickFunctionId()) {
					ScriptManager::Instance()->runFunction<sol::optional<bool>>(c.clickableComponent.getOnClickFunctionId(), c.tientity);
				}
            }
        }
    }
}
