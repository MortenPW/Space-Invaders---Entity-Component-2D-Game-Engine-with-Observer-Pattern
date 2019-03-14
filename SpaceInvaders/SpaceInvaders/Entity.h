#ifndef ENTITY
#define ENTITY
#include "Vector2D.h"
#include <vector>
#include "ComponentCom.h"

namespace game
{
	class Component;

	class Entity
	{
	public:
		// Location and size
		Vector2D<int> position;
		Vector2D<int> dimension;
		Vector2D<int> velocity;

		explicit Entity();
		virtual ~Entity();

		void update();

		void add(Component* component);
		void set_position(int x, int y);
		unsigned int id() const;

		std::string texture() const;
		void set_texture(const std::string& texture);
		int base_speed() const;
		void set_base_speed(int base_speed);

		ComponentCom<std::string>& communication();

	private:
		static unsigned int entity_counter_; /// Problematic if entities surpass int
		unsigned int id_;

		std::string texture_;
		int base_speed_;

		std::vector<Component*> components_;
		//std::vector<std::shared_ptr<Component>> components_; // Problems with polymorphism (probably casting err.)-
		// use static_cast<Component*>(components_.back().get()) if you know that all objects have type Component
		// https://stackoverflow.com/questions/15762176/c11-smart-pointers-and-polymorphism

		ComponentCom<std::string> communication_; // Shared data / events between components
	};
}

#endif
