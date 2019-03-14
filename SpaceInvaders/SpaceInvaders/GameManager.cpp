#include "GameManager.h"
#include "InputManager.h"
#include <chrono>;
#include "EntityManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "TextManager.h"


game::GameManager& game::GameManager::instance()
{
	/// Automatically thread-safe since C++11
	/// §6.7[stmt.dcl] p4:
	/// If control enters the declaration concurrently while the variable is being initialized, 
	/// the concurrent execution shall wait for completion of the initialization.
	/// Being static, it only gets initialized once.
	static GameManager instance;
	return instance;
}

game::GameManager::GameManager()
	: ended_game_(false), game_over_(false)
{
	/// Running game loop here would result in endless loop,
	/// therefore, we use main to initialize the game with this singleton
}

bool game::GameManager::ended_game() const
{
	return ended_game_;
}

void game::GameManager::set_ended_game(const bool ended_game)
{
	ended_game_ = ended_game;
}

bool game::GameManager::game_over() const
{
	return game_over_;
}

void game::GameManager::set_game_over(const bool game_over)
{
	game_over_ = game_over;
}

bool game::GameManager::game_won() const
{
	if (!game_over_)
	{
		for (auto& entity : EntityManager::instance().entities())
		{
			if (entity->id() > ResourceManager::instance().aliens_start_id)
			{
				if (entity->position.y() > 0)
				{
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

void game::GameManager::configure_game()
{
	RenderManager::instance().init_window();
	ResourceManager::instance().load_scene();
}

void game::GameManager::run_updates()
{
	RenderManager::instance().render_clear();
	InputManager::instance().update();
	EntityManager::instance().update();
	TextManager::instance().score_text();
	if (game_over_)
	{
		TextManager::instance().game_center_text("Game over!");
	}
	else if (game_won())
	{
		TextManager::instance().game_center_text("Game won!");
	}
	RenderManager::instance().render_update();
}

void game::GameManager::game_loop()
{
	using clock = std::chrono::high_resolution_clock;

	// Fixed timestep of 1 / (60 fps) = 16 milliseconds
	const std::chrono::nanoseconds timestep(std::chrono::milliseconds(16));
	std::chrono::nanoseconds lag(std::chrono::milliseconds(0));
	auto time_start = clock::now();

	while (!ended_game_)
	{
		const auto delta_time = clock::now() - time_start;
		time_start = clock::now();
		lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

		while (lag >= timestep)
		{
			lag -= timestep;

			run_updates();

			// TODO: Should implement interpolation for smoother rendering
		}
	}
}
