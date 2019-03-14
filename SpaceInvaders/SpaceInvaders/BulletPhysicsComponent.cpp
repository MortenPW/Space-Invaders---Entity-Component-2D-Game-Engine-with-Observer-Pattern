#include "BulletPhysicsComponent.h"
#include "PhysicsManager.h"
#include "EntityManager.h"
#include "TextManager.h"
#include "ResourceManager.h"


game::BulletPhysicsComponent::BulletPhysicsComponent(Entity* entity) : PhysicsComponent(entity)
{
	SDL_Rect collider; /// Simple box collider
	collider.w = entity_->dimension.x();
	collider.h = entity_->dimension.y();
	collider.x = entity_->position.x();
	collider.y = entity_->position.y();
	PhysicsManager::instance().add(entity_->id(), collider);
}

void game::BulletPhysicsComponent::collider_collisions(SDL_Rect& collider) const
{
	// If collided
	for (auto const& entity : EntityManager::instance().entities())
	{
		if (entity->id() != 1) // Don't crash into player
		{
			// Avoid self collisions
			if (entity->id() != entity_->id())
			{
				auto& compared_collider = PhysicsManager::instance().collider_map().at(entity->id());

				if (SDL_HasIntersection(&collider, &compared_collider))
				{
					//entity_->position.set_y(entity_->position.y() - entity_->velocity.y());
					entity_->position.set_x(-1000);
					collider.y = entity_->position.y();

					if (entity->id() >= ResourceManager::instance().aliens_start_id)
					{
						TextManager::instance().increment_score();
 					}
				}
			}
		}
	}
}