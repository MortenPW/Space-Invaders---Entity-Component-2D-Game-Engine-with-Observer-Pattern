#include "BombInputComponent.h"
#include "EntityManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include <ctime>

game::BombInputComponent::BombInputComponent(Entity* entity) : Component(entity)
{
}

void game::BombInputComponent::update()
{
	static auto counter = 0;
	if (counter > ResourceManager::instance().bomb_speed)
	{
		auto& entities = EntityManager::instance().entities();
		std::vector<Vector2D<int>> bombers_pos;
		std::vector<int> bombers_dimension;

		for (auto it = entities.begin(); it != entities.end(); ++it)
		{
			if (it->get()->position.y() > -500 && it->get()->id() > ResourceManager::instance().aliens_start_id)
			{
				bombers_pos.push_back(it->get()->position);
				bombers_dimension.push_back(it->get()->dimension.x());
			}
		}

		if (!bombers_pos.empty()) // null guard
		{
			srand(time(nullptr));
			const auto random = rand() % bombers_pos.size();
			entity_->position = bombers_pos.at(random);
			entity_->position.set_x(entity_->position.x() + bombers_dimension.at(random) / 2);
		}
		counter = 0;
	}
	++counter;

	// Current velocity
	auto y = 0;
	y += entity_->base_speed();

	// Set position according to momentum
	entity()->velocity.set_y(y);
	entity()->position += entity()->velocity;
}
