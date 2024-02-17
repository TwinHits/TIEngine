#ifndef TIENTITY_H
#define TIENTITY_H

#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics.hpp>

#include "objects/GlobalId.h"
#include "objects/components/Component.h"
#include "templates/MakeUnique.h"

namespace TIE {

class TIEntity {
	public:
		TIEntity();
		virtual ~TIEntity() {};

		template<typename T>
		T& addComponent() {
			if (!this->hasComponent<T>()) {
				components[typeid(T)] = make_unique<T>();
			}
			return *this->getComponent<T>();
		}

		template <typename T>
		bool hasComponent() const {
			return components.count(typeid(T));
		}
		
		template <typename T>
		T* getComponent() {
			if (this->hasComponent<T>()) {
				return static_cast<T*>(components.at(typeid(T)).get());
			}
			return nullptr;
		}

		template <typename T>
		bool removeComponent() {
			if (components.count(typeid(T))) {
				components.erase(typeid(T));
				return true;
			}
			return false;
		}

		virtual void update(const float) {};

		GlobalId getId() const;

		void setParent(TIEntity*);
		TIEntity& getParent();
		bool hasParent();

		void setRemove(bool);
		bool getRemove() const;

		void setName(const std::string&);
		const std::string& getName() const;

		bool hasChildren();
		std::vector<std::unique_ptr<TIEntity> >& getChildren();
		TIEntity& attachChild(std::unique_ptr<TIEntity>);
		TIEntity& attachChild();

		virtual bool isSceneLayer();

		bool isRelatedTo(TIEntity&);
		bool isParentOf(TIEntity&);

		bool operator==(const TIEntity&) const;
		bool operator!=(const TIEntity&) const;
	private:
		std::unordered_map<std::type_index, std::unique_ptr<Component> > components;
		GlobalId id = -1;
		bool remove = false;
		std::string name = "";
		TIEntity* parent = nullptr;
		std::vector<std::unique_ptr<TIEntity> > children;

		std::unique_ptr<TIEntity> detachChild(const TIEntity&);

		void operator=(const TIEntity&);
};

}
#endif
