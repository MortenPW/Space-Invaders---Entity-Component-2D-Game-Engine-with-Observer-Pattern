#ifndef PLAYERPHYSICSCOMPONENT
#define PLAYERPHYSICSCOMPONENT

#include "Component.h"
#include <SDL.h>
#include "PhysicsComponent.h"

namespace game
{
	class PlayerPhysicsComponent : public PhysicsComponent
	{
	public:
		explicit PlayerPhysicsComponent(Entity* entity);
		~PlayerPhysicsComponent();

		void collider_collisions(SDL_Rect& collider) const override;
	};
}

#endif
