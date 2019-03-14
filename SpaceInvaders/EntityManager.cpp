#include "EntityManager.h"
#include "ResourceManager.h"


game::EntityManager& game::EntityManager::instance()
{
	static EntityManager instance;
	return instance;
}

game::EntityManager::EntityManager()
{
}

void game::EntityManager::update()
{
	// TODO: Vurder å dele opp i flere entities for bedre kontroll av bomber og aliens.
	for (auto const& entity : entities_)
	{
		if (entity->position.y() > -500) // Only update entities inside y. Send live entities to x (a better system would map entities and remove them).
		{
			entity->update();
		}
	}

	for (auto const& explosion : ResourceManager::instance().explosions())
	{
		explosion->update();
	}
}

const std::vector<std::unique_ptr<game::Entity>>& game::EntityManager::entities() const
{
	return entities_;
}

game::Entity& game::EntityManager::entity_by_id(const int id) const
{
	return *entities_.at(id - 1);
}

int game::EntityManager::register_entity(std::unique_ptr<Entity>& entity)
{
	if (!entity.get())
	{
		return -1; // Null guard
	}

	// TODO: Gjør til map med id for enklere aksess etterhvert som ting fjernes og legges til
	entities_.push_back(move(entity));

	return 0;
}

template <typename T>
void game::EntityManager::remove(std::vector<std::unique_ptr<Entity>>& v, const T& item)
{
	v.erase(std::remove(v.begin(), v.end(), item), v.end());
}
