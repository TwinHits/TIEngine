#ifndef HOVERABLECOMPONENT_H
#define HOVERABLECOMPONENT_H

#include "objects/components/Component.h"

#include <functional>

#include "objects/GlobalId.h"
#include "objects/Message.h"

namespace TIE {

	class HoverableComponent : public Component {
	public:
		HoverableComponent() {};
		virtual ~HoverableComponent() {};

		void setHoverable(const bool);
		const bool isHoverable();
		const bool isHoverable() const;

		void setOnHoverFunction(std::function<void(Message&)>);
		const std::function<void(Message&)> getOnHoverFunction();

		void setOnHoverFunctionId(const GlobalId);
		const GlobalId getOnHoverFunctionId();
	private:
		bool hoverable = true;
		std::function<void(Message&)> onHoverFunction = nullptr;
		GlobalId onHoverFunctionId = 0;
	};

}
#endif
