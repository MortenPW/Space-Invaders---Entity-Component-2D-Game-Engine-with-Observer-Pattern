#ifndef PHYSICSMANAGER
#define PHYSICSMANAGER
#include <SDL_rect.h>
#include <map>

namespace game
{
	class PhysicsManager
	{
	public:
		static PhysicsManager& instance();

		// Disable assignemant operators
		PhysicsManager(PhysicsManager const&) = delete;
		PhysicsManager& operator=(PhysicsManager const&) = delete;

		void add(unsigned id, SDL_Rect collider);
		void remove(unsigned id);
		std::map<unsigned int, SDL_Rect>& collider_map();

	private:
		explicit PhysicsManager();
		~PhysicsManager();

		std::map<unsigned int, SDL_Rect> collider_map_;
	};
}

#endif
