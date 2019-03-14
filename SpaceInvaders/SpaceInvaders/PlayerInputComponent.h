#ifndef PLAYERINPUTCOMPONENT
#define PLAYERINPUTCOMPONENT

#include "Component.h"

namespace game 
{
	class PlayerInputComponent : public Component
	{
	public:
		explicit PlayerInputComponent(Entity* entity);

		void update() override;
	};
}

#endif
