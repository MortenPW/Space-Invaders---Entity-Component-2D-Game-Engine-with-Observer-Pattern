#include "ExplosionsPhysicsComponent.h"
#include "PhysicsManager.h"


game::ExplosionsPhysicsComponent::ExplosionsPhysicsComponent(Entity* entity) : Component(entity)
{
	SDL_Rect collider; /// Simple box collider
	collider.w = entity_->dimension.x() * 0;
	collider.h = entity_->dimension.y() * 0;
	collider.x = entity_->position.x();
	collider.y = entity_->position.y();
	PhysicsManager::instance().add(entity_->id(), collider);
}

game::ExplosionsPhysicsComponent::~ExplosionsPhysicsComponent()
{
	PhysicsManager::instance().remove(entity_->id());
}


void game::ExplosionsPhysicsComponent::update()
{
}
