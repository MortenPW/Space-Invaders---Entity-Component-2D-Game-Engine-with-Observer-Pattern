#include "TextManager.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "RenderManager.h"
#include "TextureManager.h"
#include "ResourceManager.h"
#include "GameManager.h"

game::TextManager& game::TextManager::instance()
{
	static TextManager instance;
	return instance;
}

game::TextManager::TextManager() : score_(0)
{
	init();
}

bool game::TextManager::init()
{
	//Initialize SDL_ttf
	return TTF_Init() == -1;
}

void game::TextManager::score_text() const
{
	auto text = "Score<" + std::to_string(score_) + ">";

	const auto sans = TTF_OpenFont("fonts/space_invaders.ttf", 18); //this opens a font style and sets a size
	const SDL_Color white = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	const auto surface_message = TTF_RenderText_Solid(sans, text.c_str(), white); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	TextureManager::instance().load_surface(surface_message, 0, RenderManager::instance().renderer());
	TextureManager::instance().draw_frame(0, 5, 5, 150, 30, 1, 0, RenderManager::instance().renderer());
}

void game::TextManager::game_center_text(const char* text) const
{
	const auto sans = TTF_OpenFont("fonts/space_invaders.ttf", 18); //this opens a font style and sets a size
	const SDL_Color white = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	const auto surface_message = TTF_RenderText_Solid(sans, text, white);
	// as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	TextureManager::instance().load_surface(surface_message, 0, RenderManager::instance().renderer());
	TextureManager::instance().draw_frame(0, 150, 100, 150, 50, 1, 0, RenderManager::instance().renderer());
}

void game::TextManager::increment_score()
{
	if (!GameManager::instance().game_over())
	{
		++score_;
	}
}
