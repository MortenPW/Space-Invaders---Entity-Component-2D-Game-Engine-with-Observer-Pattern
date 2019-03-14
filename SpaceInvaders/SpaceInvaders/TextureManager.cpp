#include "TextureManager.h"
#include <iostream>


game::TextureManager& game::TextureManager::instance()
{
	static TextureManager instance;
	return instance;
}

game::TextureManager::TextureManager()
{

}

int game::TextureManager::image_width(const int id)
{
	int w, h;
	SDL_QueryTexture(texture_map_[id], nullptr, nullptr, &w, &h);
	return w;
}

int game::TextureManager::image_height(const int id)
{
	int w, h;
	SDL_QueryTexture(texture_map_[id], nullptr, nullptr, &w, &h);
	return h;
}

bool game::TextureManager::load_surface(SDL_Surface* load_surface, const int id, SDL_Renderer* renderer)
{
	const auto texture = SDL_CreateTextureFromSurface(renderer, load_surface); // Pass Surface to Texture
	SDL_FreeSurface(load_surface); //Delete Surface

	if (!texture) // exception handle transiction Surfacte to Texture
	{
		std::cout << "error creating texture of surface: " << std::endl;
		return false;
	}

	texture_map_[id] = texture; // save texture

	return true;
}

bool game::TextureManager::load(const std::string path, const int id, SDL_Renderer* renderer)
{
	const auto surface = IMG_Load(path.c_str()); // create Surface with contents of file name

	if (!surface) // exception handle load error
	{
		std::cout << "error loading file: " << path << std::endl;
		return false;
	}

	const auto texture = SDL_CreateTextureFromSurface(renderer, surface); // Pass Surface to Texture
	SDL_FreeSurface(surface); //Delete Surface

	if (!texture) // exception handle transiction Surfacte to Texture
	{
		std::cout << "error creating texture of file: " << path << std::endl;
		return false;
	}

	texture_map_[id] = texture; // save texture

	return true;
}

void game::TextureManager::draw(const int id, const int x, const int y, const int width,
	const int height, SDL_Renderer* renderer, const SDL_RendererFlip flip)
{
	SDL_Rect src_rect; // source rectangle
	SDL_Rect dest_rect; // destination rectangle

	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.w = dest_rect.w = width;
	src_rect.h = dest_rect.h = height;
	dest_rect.x = x; // select x axis on game window
	dest_rect.y = y; // select y axis on game window

	SDL_RenderCopyEx(renderer, texture_map_[id], &src_rect, &dest_rect, 0, nullptr, flip); // Load image to render buffer
}

void game::TextureManager::draw_frame(const int id, const int x, const int y, const int width, const int height,
	const int current_row, const int current_frame, SDL_Renderer* renderer, const SDL_RendererFlip flip)
{
	SDL_Rect src_rect; // source rectangle
	SDL_Rect dest_rect; // destination rectangle

	src_rect.x = width * current_frame;
	src_rect.y = height * (current_row - 1);
	src_rect.w = dest_rect.w = width;
	src_rect.h = dest_rect.h = height;
	dest_rect.x = x;
	dest_rect.y = y;

	SDL_RenderCopyEx(renderer, texture_map_[id], &src_rect, &dest_rect, 0, nullptr, flip); // Load current frame on the buffer game
}

void game::TextureManager::clear_from_texture_map(const int id)
{
	texture_map_.erase(id);
}

const std::map<int, SDL_Texture*>& game::TextureManager::texture_map() const
{
	return texture_map_;
}
