#include "RenderManager.h"
#include <SDL_image.h>
#include <iostream>
#include "ResourceManager.h"


game::RenderManager& game::RenderManager::instance()
{
	static RenderManager instance;
	return instance;
}

game::RenderManager::RenderManager()
	: window_(nullptr), renderer_(nullptr)
{
	
}

game::RenderManager::~RenderManager()
{
	clean_sdl();
}

SDL_Window* const& game::RenderManager::window() const
{
	return window_;
}

void game::RenderManager::set_window(SDL_Window* window)
{
	window_ = window;
}

SDL_Renderer* const& game::RenderManager::renderer() const
{
	return renderer_;
}

void game::RenderManager::set_renderer(SDL_Renderer* renderer)
{
	renderer_ = renderer;
}

void game::RenderManager::render_background(const int r, const int g, const int b, const int a) const
{
	SDL_SetRenderDrawColor(renderer_, r, g, b, a);
}

void game::RenderManager::render_clear() const
{
	SDL_RenderClear(renderer_); // clean renderer
}

void game::RenderManager::render_update() const
{
	int r, g, b, a;
	ResourceManager::instance().scene_background(r, g, b, a); // get background
	render_background(r, g, b, a);

	SDL_RenderPresent(renderer_); // draw in window
}

void game::RenderManager::init_window()
{
	int width, height;
	ResourceManager::instance().screen_dimensions(width, height);

	// Start up SDL and create window
	if (!init_sdl(ResourceManager::instance().window_title().c_str(), width, height))
	{
		std::cout << "Failed to initialize!" << std::endl;
	}
	else
	{
		//SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN_DESKTOP); /// fullscreen
		renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	}
}

bool game::RenderManager::init_sdl(const char* window_title, const int width, const int height)
{
	// Initialization flag
	auto success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError();
		success = false;
	}
	else
	{
		// Create window
		window_ = SDL_CreateWindow(window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
			height, SDL_WINDOW_SHOWN);

		if (!window_)
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			// Get window surface
			SDL_GetWindowSurface(window_);
		}
	}

	if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
	{
		std::cout << "could not init SDL_Image" << std::endl;
		std::cout << "Reason: " << IMG_GetError() << std::endl;
	}
	return success;
}

void game::RenderManager::clean_sdl() const
{
	// Deallocate surface
	SDL_DestroyWindow(window_);
	SDL_DestroyRenderer(renderer_);
	SDL_Quit();
	IMG_Quit();
}