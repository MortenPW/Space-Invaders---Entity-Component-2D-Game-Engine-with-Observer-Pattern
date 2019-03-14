#ifndef BULLETINPUTCOMPONENT
#define BULLETINPUTCOMPONENT

#include "Component.h"

namespace game
{
	class BulletInputComponent : public Component
	{
	public:
		explicit BulletInputComponent(Entity* entity);

		void update() override;
	};
}

#endif
