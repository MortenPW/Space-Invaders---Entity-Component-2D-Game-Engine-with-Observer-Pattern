#ifndef BOMBINPUTCOMPONENT
#define BOMBINPUTCOMPONENT

#include "Component.h"

namespace game
{
	class BombInputComponent : public Component
	{
	public:
		explicit BombInputComponent(Entity* entity);

		void update() override;
	};
}

#endif
