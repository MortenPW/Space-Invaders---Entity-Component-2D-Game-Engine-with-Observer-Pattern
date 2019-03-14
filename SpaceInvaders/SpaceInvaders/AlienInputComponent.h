#ifndef ALIENINPUTCOMPONENT
#define ALIENINPUTCOMPONENT

#include "Component.h"

namespace game
{
	class AlienInputComponent : public Component
	{
	public:
		explicit AlienInputComponent(Entity* entity);
		void wall_crashed();
		void drop_bomb();

		void update() override;
	};
}

#endif
