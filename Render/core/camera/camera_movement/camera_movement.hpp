#pragma once

namespace kr{
	// Defines several possible options for camera movement. 
	//Used as abstraction to stay away from window-system specific 
	//input methods
	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};
}
