#include "BulletInputComponent.h"
#include "InputManager.h"
#include "EntityManager.h"


game::BulletInputComponent::BulletInputComponent(Entity* entity) : Component(entity)
{
}

void game::BulletInputComponent::update()
{
	if (InputManager::instance().key_down(SDL_SCANCODE_SPACE))
	{
		entity()->position = EntityManager::instance().entity_by_id(1).position;

		entity()->position.set_x(entity()->position.x() + EntityManager::instance().entity_by_id(1).dimension.x() / 2);
	}

	// Current velocity
	auto y = 0;
	y -= entity_->base_speed();

	// Set position according to momentum
	entity()->velocity.set_y(y);
	entity()->position += entity()->velocity;
}
