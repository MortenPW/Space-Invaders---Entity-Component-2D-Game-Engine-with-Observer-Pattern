#ifndef EXPLOSIONSPHYSICSCOMPONENT
#define EXPLOSIONSPHYSICSCOMPONENT

#include "Component.h"

namespace game
{
	class ExplosionsPhysicsComponent : public Component
	{
	public:
		explicit ExplosionsPhysicsComponent(Entity* entity);
		~ExplosionsPhysicsComponent();

		void update() override;
	};
}

#endif
