#ifndef RENDERMANAGER
#define RENDERMANAGER
#include <SDL.h>

namespace game
{
	class RenderManager
	{
	public:
		static RenderManager& instance();

		// Disable assignemant operators
		RenderManager(RenderManager const&) = delete;
		RenderManager& operator=(RenderManager const&) = delete;

		SDL_Window* const& window() const;
		void set_window(SDL_Window* window);
		SDL_Renderer* const& renderer() const;
		void set_renderer(SDL_Renderer* renderer);

		void render_background(int r, int g, int b, int a) const;
		void render_clear() const;
		void render_update() const;

		void init_window();

	private:
		explicit RenderManager();
		~RenderManager();

		bool init_sdl(const char* window_title, int width, int height);
		void clean_sdl() const;

		// The window we'll be rendering to
		SDL_Window* window_;
		SDL_Renderer* renderer_;
	};
}

#endif
