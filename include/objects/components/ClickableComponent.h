#ifndef CLICKABLECOMPONENT_H
#define CLICKABLECOMPONENT_H

#include "objects/components/Component.h"

#include <functional>

#include "objects/GlobalId.h"
#include "objects/Message.h"

namespace TIE {

	class ClickableComponent : public Component {
	public:
		ClickableComponent() {};
		virtual ~ClickableComponent() {};

		void setClickable(const bool);
		const bool isClickable();
		const bool isClickable() const;

		void setOnClickFunction(std::function<void(Message&)>);
		const std::function<void(Message&)> getOnClickFunction();

		void setOnClickFunctionId(const GlobalId);
		const GlobalId getOnClickFunctionId();
	private:
		bool clickable = true;
		std::function<void(Message&)> onClickFunction = nullptr;
		GlobalId onClickFunctionId = 0;
	};

}
#endif
