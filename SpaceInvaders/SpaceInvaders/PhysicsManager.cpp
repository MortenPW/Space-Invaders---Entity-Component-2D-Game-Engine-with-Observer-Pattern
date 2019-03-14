#include "PhysicsManager.h"
#include <SDL.h>


game::PhysicsManager::PhysicsManager()
{
}

game::PhysicsManager::~PhysicsManager()
{
	collider_map_.clear();
}

game::PhysicsManager& game::PhysicsManager::instance()
{
	static PhysicsManager instance;
	return instance;
}

void game::PhysicsManager::add(const unsigned id, SDL_Rect collider)
{
	collider_map_.insert_or_assign(id, collider);
}

void game::PhysicsManager::remove(const unsigned id)
{
	collider_map_.erase(id);
}

std::map<unsigned int, SDL_Rect>& game::PhysicsManager::collider_map()
{
	return collider_map_;
}
