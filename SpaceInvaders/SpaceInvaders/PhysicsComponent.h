#ifndef PHYSICSCOMPONENT
#define PHYSICSCOMPONENT

#include "Component.h"
#include <SDL.h>

namespace game
{
	class PhysicsComponent : public Component
	{
	public:
		explicit PhysicsComponent(Entity* entity);
		~PhysicsComponent();

		void update() override;

		virtual void wall_collisions(SDL_Rect& collider) const;
		virtual void collider_collisions(SDL_Rect& collider) const;
	};
}

#endif
