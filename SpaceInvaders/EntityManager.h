#ifndef ENTITYMANAGER
#define ENTITYMANAGER

#include <vector>
#include "Entity.h"
#include <memory>

namespace game
{
	class EntityManager
	{
	public:
		static EntityManager& instance();

		// Disable assignemant operators
		EntityManager(EntityManager const&) = delete;
		EntityManager& operator=(EntityManager const&) = delete;

		void update();

		const std::vector<std::unique_ptr<Entity>>& entities() const;

		Entity& entity_by_id(int id) const;
		int register_entity(std::unique_ptr<Entity>& entity);

		template<typename T>
		void remove(std::vector<std::unique_ptr<Entity>>& v, const T& item);

	private:
		explicit EntityManager();

		std::vector<std::unique_ptr<Entity>> entities_;
	};
}

#endif
