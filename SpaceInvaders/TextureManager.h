#ifndef TEXTUREMANAGER
#define TEXTUREMANAGER

#include <string>
#include <map>
#include <SDL_image.h>

namespace game
{
	class TextureManager
	{
	public:
		static TextureManager& instance();

		// Disable assignemant operators
		TextureManager(TextureManager const&) = delete;
		TextureManager& operator=(TextureManager const&) = delete;

		void update();

		// Load image with the file name, and assigns an id
		bool load(std::string path, int id, SDL_Renderer* renderer);

		// Get image dimensions
		int image_width(int id);
		int image_height(int id);
		bool load_surface(SDL_Surface* load_surface, const int id, SDL_Renderer* renderer);

		// Draw static image
		void draw(int id, int x, int y, int width, int height,
		          SDL_Renderer* renderer, SDL_RendererFlip = SDL_FLIP_NONE);

		// Draw image sprite
		void draw_frame(int id, int x, int y, int width, int height,
		          int current_row, int current_frame, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

		// Delete SDL_Texture from map
		void clear_from_texture_map(int id);
		const std::map<int, SDL_Texture*>& texture_map() const;

	private:
		explicit TextureManager();

		std::map<int, SDL_Texture*> texture_map_; // Map with all SDL_Textures
	};
}

#endif
