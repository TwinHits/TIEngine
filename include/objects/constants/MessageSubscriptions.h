#ifndef MESSAGESUBSCRIPTIONS_H
#define MESSAGESUBSCRIPTIONS_H

#include <string>

namespace TIE {

class MessageSubscriptions {
	public:
		const static inline std::string WINDOW_SIZE_CHANGE = "window.size.change";
		const static inline std::string ACTIVE_VIEW_CHANGE = "view.active.change";
		const static inline std::string MOUSE_BUTTON_PRESSED = "MOUSEBUTTONPRESSED";
		const static inline std::string BEHAVIOR_TREE_NODE_UPDATED = "BehaviorTreeNodeUpdated";
};

}

#endif
