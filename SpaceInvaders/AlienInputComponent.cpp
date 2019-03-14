#include "AlienInputComponent.h"
#include "ResourceManager.h"
#include "EntityManager.h"

game::AlienInputComponent::AlienInputComponent(Entity* entity) : Component(entity)
{
}

void game::AlienInputComponent::wall_crashed()
{
	if (ResourceManager::instance().aliens_down)
	{
		ResourceManager::instance().move_right = !ResourceManager::instance().move_right;
		ResourceManager::instance().aliens_down = false;

		for (auto &entity : EntityManager::instance().entities()) 
		{
			if (entity->id() >= ResourceManager::instance().aliens_start_id - 1)
			{
				// Current velocity
				const auto y = 0;

				// Set position according to momentum
				entity->velocity.set_y(y);
				entity->velocity.set_x(0);
				entity->position += entity->velocity;

				entity->position.set_y(entity->position.y() + 10);
			}
		}
	}
}

void game::AlienInputComponent::drop_bomb()
{
	if (ResourceManager::instance().drop_bomb)
	{
		ResourceManager::instance().drop_bomb = false;
	}
}

void game::AlienInputComponent::update()
{
	// Current velocity
	auto x = 0;
	
	if (ResourceManager::instance().move_right)
	{
		x += entity_->base_speed();
	}
	else
	{
		x -= entity_->base_speed();
	}

	entity()->velocity.set_x(x);
	entity()->position += entity()->velocity;
		
	wall_crashed();
}
