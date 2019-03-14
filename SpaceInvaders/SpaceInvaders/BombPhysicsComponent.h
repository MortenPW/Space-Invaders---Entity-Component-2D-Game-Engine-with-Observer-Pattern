#ifndef BOMBPHYSICSCOMPONENT
#define BOMBPHYSICSCOMPONENT

#include "Component.h"
#include "PhysicsComponent.h"

namespace game
{
	class BombPhysicsComponent : public PhysicsComponent
	{
	public:
		explicit BombPhysicsComponent(Entity* entity);

		void collider_collisions(SDL_Rect& collider) const override;
	};
}

#endif
