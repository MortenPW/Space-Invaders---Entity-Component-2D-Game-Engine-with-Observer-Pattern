#include "PlayerPhysicsComponent.h"
#include "PhysicsManager.h"
#include "EntityManager.h"


game::PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* entity) : PhysicsComponent(entity)
{
	SDL_Rect collider; /// Simple box collider
	collider.w = entity_->dimension.x();
	collider.h = entity_->dimension.y();
	collider.x = entity_->position.x();
	collider.y = entity_->position.y();
	PhysicsManager::instance().add(entity_->id(), collider);
}

game::PlayerPhysicsComponent::~PlayerPhysicsComponent()
{
	PhysicsManager::instance().remove(entity_->id());
}

void game::PlayerPhysicsComponent::collider_collisions(SDL_Rect& collider) const
{
	// If collided
	for (auto const& entity : EntityManager::instance().entities())
	{
		// Avoid self collisions
		if (entity->id() != entity_->id())
		{
			auto& compared_collider = PhysicsManager::instance().collider_map().at(entity->id());

			if (SDL_HasIntersection(&collider, &compared_collider))
			{
				entity_->position.set_y(-3000);
			}

			if (SDL_HasIntersection(&collider, &compared_collider))
			{
				entity_->position.set_y(-3000);
			}
		}
	}
}