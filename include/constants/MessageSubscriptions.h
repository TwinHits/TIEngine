#ifndef MESSAGESUBSCRIPTIONS_H
#define MESSAGESUBSCRIPTIONS_H

#include <string>

namespace TIE {

class MessageSubscriptions {
	public:
		const static inline std::string LOG_ENTERED = "LOG_ENTERED";

		const static inline std::string WINDOW_SIZE_CHANGE = "window.size.change";
		const static inline std::string ACTIVE_VIEW_CHANGE = "view.active.change";

		const static inline std::string LEFT_MOUSE_BUTTON_PRESSED = "LEFTMOUSEBUTTONPRESSED";
		const static inline std::string RIGHT_MOUSE_BUTTON_PRESSED = "RIGHTMOUSEBUTTONPRESSED";
		
		const static inline std::string BEHAVIOR_TREE_NODE_SUCCESS = "BehaviorTreeNodeSuccess";
		const static inline std::string BEHAVIOR_TREE_NODE_RUNNING = "BehaviorTreeNodeRunning";
		const static inline std::string BEHAVIOR_TREE_NODE_FAILURE = "BehaviorTreeNodeFailure";
};

}

#endif
