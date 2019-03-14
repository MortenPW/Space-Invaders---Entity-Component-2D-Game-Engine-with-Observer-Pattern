#include "PhysicsManager.h"
#include "EntityManager.h"
#include "AlienPhysicsComponent.h"
#include "ComponentCom.h"
#include "ResourceManager.h"
#include "AlienInputComponent.h"
#include "GameManager.h"


game::AlienPhysicsComponent::AlienPhysicsComponent(Entity* entity) : PhysicsComponent(entity)
{
	SDL_Rect collider; /// Simple box collider
	collider.w = entity_->dimension.x();
	collider.h = entity_->dimension.y();
	collider.x = entity_->position.x();
	collider.y = entity_->position.y();
	PhysicsManager::instance().add(entity_->id(), collider);
}

void game::AlienPhysicsComponent::wall_collisions(SDL_Rect& collider) const
{
	int screen_width, screen_height;
	ResourceManager::instance().screen_dimensions(screen_width, screen_height); // If they change run-time

	if (!ResourceManager::instance().aliens_down)
	{	
		// Screen border
		if (entity_->position.x() <= 0 || entity_->position.x() + entity_->dimension.x() >= screen_width)
		{
			/// Apply equal force back
			ResourceManager::instance().aliens_down = true;
		}
	}

	if (entity_->position.y() <= 0 || entity_->position.y() + entity_->dimension.y() >= screen_height)
	{
		/// Apply equal force back
		entity_->position.set_y(entity_->position.y() - entity_->velocity.y());
	}

	if (entity_->position.y() > EntityManager::instance().entity_by_id(1).position.y())
	{
		GameManager::instance().set_game_over(true);
		entity_->position.set_y(-3000);
	}
}

void game::AlienPhysicsComponent::collider_collisions(SDL_Rect& collider) const
{
	// If collided
	for (auto const& entity : EntityManager::instance().entities())
	{
		if (entity->id() <= ResourceManager::instance().aliens_start_id - 1 
			&& entity->id() != 3
			&& entity->id() != 4
			&& entity->id() != 5) // Don't crash into aliens or bombs
		{
			// Avoid self collisions
			if (entity->id() != entity_->id())
			{
				auto& compared_collider = PhysicsManager::instance().collider_map().at(entity->id());

				if (SDL_HasIntersection(&collider, &compared_collider))
				{
					entity_->position.set_x(entity_->position.x() - entity_->velocity.x());
					collider.x = entity_->position.x();

					if (entity->id() == 1)
					{
						GameManager::instance().set_game_over(true);
						entity->position.set_y(-3000);
					}
				}

				if (SDL_HasIntersection(&collider, &compared_collider))
				{
					entity_->position.set_y(-3000);
					collider.y = entity_->position.y();

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