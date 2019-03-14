#ifndef COMPONENT
#define COMPONENT

#include "Entity.h"

namespace game
{
	class Entity;

	class Component
	{
	public:
		explicit Component(Entity* entity) : entity_(entity) {}
		virtual ~Component();

		virtual void update() = 0;

		Entity* entity() const;

	protected:
		Entity* entity_;
	};

	inline Component::~Component()
	= default;

	inline Entity* Component::entity() const
	{
		return entity_;
	}
}

#endif
