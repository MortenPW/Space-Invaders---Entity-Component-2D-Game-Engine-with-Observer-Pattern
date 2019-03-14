#ifndef RESOURCEMANAGER
#define RESOURCEMANAGER
#include "Entity.h"
#include <memory>

namespace game
{
	class ResourceManager
	{
	public:
		// TODO: An extremely crude and basic resource manager (single state)- more like a reference / level.
		// TODO: Should deserialize json or xml files based on scene dependencies into current state / scene / window
		static ResourceManager& instance();

		// Disable assignemant operators
		ResourceManager(ResourceManager const&) = delete;
		ResourceManager& operator=(ResourceManager const&) = delete;

		std::string window_title() const;
		void update_screen_dimensions();
		void screen_dimensions(int& width, int& height) const;
		void load_scene() const;
		void scene_background(int& r, int& g, int& b, int& a) const;

		int screen_width() const;
		int screen_height() const;

		void add_explosion(int x, int y);
		void human_player() const;
		void bullet() const;
		void bomb() const;
		void shields() const;
		void aliens() const;

		const std::vector<std::unique_ptr<Entity>>& explosions() const;

		// Temp hacks due to problems with observable pattern (ComponentCom)
		int aliens_start_id = 11;
		bool aliens_down = false;
		bool move_right = false;
		bool drop_bomb = false;
		int drop_bomb_id = 11;
		int bomb_speed = 100;

	private:
		explicit ResourceManager();

		std::vector<std::unique_ptr<Entity>> explosions_;

		// TODO: Could get screen size from SDL_GetWindowSize
		// TODO: Multiplier does not seem to work- problem changing dimensions of rect
		int size_multiplier_ = 2;
		int screen_width_ = 224 * size_multiplier_;
		int screen_height_ = 256 * size_multiplier_;
	};
}

#endif
