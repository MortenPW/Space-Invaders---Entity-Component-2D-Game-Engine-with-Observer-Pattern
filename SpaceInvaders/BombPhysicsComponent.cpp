#include "PhysicsManager.h"
#include "EntityManager.h"
#include "BombPhysicsComponent.h"
#include "ResourceManager.h"
#include "GameManager.h"


game::BombPhysicsComponent::BombPhysicsComponent(Entity* entity) : PhysicsComponent(entity)
{
	SDL_Rect collider; /// Simple box collider
	collider.w = entity_->dimension.x();
	collider.h = entity_->dimension.y();
	collider.x = entity_->position.x();
	collider.y = entity_->position.y();
	PhysicsManager::instance().add(entity_->id(), collider);
}

void game::BombPhysicsComponent::collider_collisions(SDL_Rect& collider) const
{
	// If collided
	for (auto const& entity : EntityManager::instance().entities())
	{
		if (entity->id() <= ResourceManager::instance().aliens_start_id) // Don't crash into aliens
		{
			// Avoid self collisions
			if (entity->id() != entity_->id())
			{
				auto& compared_collider = PhysicsManager::instance().collider_map().at(entity->id());

				if (SDL_HasIntersection(&collider, &compared_collider))
				{
					entity_->position.set_x(entity_->position.x() - entity_->velocity.x());
					collider.x = entity_->position.x();

					ResourceManager::instance().add_explosion(entity_->position.x(), entity_->position.y());

					if (entity->id() == 1)
					{
						GameManager::instance().set_game_over(true);
						entity->position.set_y(-3000);
					}
				}

				// Hack for sliding
				if (SDL_HasIntersection(&collider, &compared_collider))
				{
					entity_->position.set_y(entity_->position.y() - entity_->velocity.y());
					collider.y = entity_->position.y();

					ResourceManager::instance().add_explosion(entity_->position.x(), entity_->position.y());

					if (entity->id() == 1)
					{
						GameManager::instance().set_game_over(true);
						entity->position.set_y(-3000);
					}
				}
			}
		}
	}
}