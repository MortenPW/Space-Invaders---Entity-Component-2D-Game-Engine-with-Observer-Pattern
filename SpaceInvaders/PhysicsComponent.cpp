#include "PhysicsComponent.h"
#include "ResourceManager.h"
#include "PhysicsManager.h"
#include "EntityManager.h"

game::PhysicsComponent::PhysicsComponent(Entity* entity): Component(entity)
{
	SDL_Rect collider; /// Simple box collider
	collider.w = entity_->dimension.x();
	collider.h = entity_->dimension.y();
	collider.x = entity_->position.x();
	collider.y = entity_->position.y();
	PhysicsManager::instance().add(entity_->id(), collider);
}

game::PhysicsComponent::~PhysicsComponent()
{
	PhysicsManager::instance().remove(entity_->id());
}

void game::PhysicsComponent::update()
{
	// Update collider
	auto& collider = PhysicsManager::instance().collider_map().at(entity_->id());
	collider.w = entity_->dimension.x();
	collider.h = entity_->dimension.y();
	collider.x = entity_->position.x();
	collider.y = entity_->position.y();

	wall_collisions(collider);
	collider_collisions(collider);
}

void game::PhysicsComponent::wall_collisions(SDL_Rect& collider) const
{
	int screen_width, screen_height;
	ResourceManager::instance().screen_dimensions(screen_width, screen_height); // If they change run-time

	// Screen border
	if (entity_->position.x() < 0 || entity_->position.x() + entity_->dimension.x() > screen_width)
	{
		/// Apply equal force back
		entity_->position.set_x(entity_->position.x() - entity_->velocity.x());
		collider.x = entity_->position.x();
	}

	if (entity_->position.y() < 0 || entity_->position.y() + entity_->dimension.y() > screen_height)
	{
		/// Apply equal force back
		entity_->position.set_y(entity_->position.y() - entity_->velocity.y());
		collider.y = entity_->position.y();
	}
}

void game::PhysicsComponent::collider_collisions(SDL_Rect& collider) const
{
	// If collided
	for (auto const& entity : EntityManager::instance().entities())
	{
		// Avoid self collisions
		if (entity->id() != entity_->id())
		{
			auto& compared_collider = PhysicsManager::instance().collider_map().at(entity->id());

			// TODO: Entity sticks on y-axis
			if (SDL_HasIntersection(&collider, &compared_collider))
			{
				entity_->position.set_x(entity_->position.x() - entity_->velocity.x());
				collider.x = entity_->position.x();
			}

			if (SDL_HasIntersection(&collider, &compared_collider))
			{
				entity_->position.set_y(entity_->position.y() - entity_->velocity.y());
				collider.y = entity_->position.y();
			}
		}
	}
}