#ifndef ALIENPHYSICSCOMPONENT
#define ALIENPHYSICSCOMPONENT

#include "Component.h"
#include "PhysicsComponent.h"

namespace game
{
	class AlienPhysicsComponent : public PhysicsComponent
	{
	public:
		explicit AlienPhysicsComponent(Entity* entity);
		void wall_collisions(SDL_Rect& collider) const override;
		void collider_collisions(SDL_Rect& collider) const override;
	};
}

#endif
