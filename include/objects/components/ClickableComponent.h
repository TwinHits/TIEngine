#ifndef CLICKABLECOMPONENT_H
#define CLICKABLECOMPONENT_H

#include "objects/components/Component.h"

#include <functional>

#include "objects/Message.h"

namespace TIE {

	class ClickableComponent : public Component {
	public:
		ClickableComponent() {};
		virtual ~ClickableComponent() {};

		void setClickable(const bool);
		const bool isClickable();
		const bool isClickable() const;

		void setOnClick(std::function<void(Message&)>);
		const std::function<void(Message&)> getOnClick();
	private:
		bool clickable = true;
		std::function<void(Message&)> onClick;
	};

}
#endif
