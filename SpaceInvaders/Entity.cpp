#include "Component.h"

unsigned int game::Entity::entity_counter_ = 0;

game::Entity::Entity()
	: position(0, 0),
	  dimension(0, 0),
	  velocity(0, 0),
	  id_(++entity_counter_),
	  base_speed_(0)
{
}

game::Entity::~Entity()
{
	components_.clear();
}

void game::Entity::add(Component* component)
{
	components_.push_back(component);
}

void game::Entity::update()
{
	for (auto const& component : components_)
	{
		component->update();
	}
}

unsigned int game::Entity::id() const
{
	return id_;
}

std::string game::Entity::texture() const
{
	return texture_;
}

void game::Entity::set_texture(const std::string& texture)
{
	texture_ = texture;
}

int game::Entity::base_speed() const
{
	return base_speed_;
}

void game::Entity::set_base_speed(const int base_speed)
{
	base_speed_ = base_speed;
}

game::ComponentCom<std::string>& game::Entity::communication()
{
	return communication_;
}
