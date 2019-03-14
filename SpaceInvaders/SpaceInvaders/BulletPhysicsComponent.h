#ifndef BULLETPHYSICSCOMPONENT
#define BULLETPHYSICSCOMPONENT

#include "Component.h"
#include "PhysicsComponent.h"

namespace game
{
	class BulletPhysicsComponent : public PhysicsComponent
	{
	public:
		explicit BulletPhysicsComponent(Entity* entity);

		void collider_collisions(SDL_Rect& collider) const override;
	};
}

#endif
