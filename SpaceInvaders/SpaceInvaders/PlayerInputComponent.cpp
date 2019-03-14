#include "InputManager.h"
#include "PlayerInputComponent.h"


game::PlayerInputComponent::PlayerInputComponent(Entity* entity): Component(entity)
{
}

void game::PlayerInputComponent::update()
{
	// Current velocity
	auto x = 0;
	auto y = 0;
	auto speed_multiplier = 1;

	// LR Shift
	if (InputManager::instance().key_still_down(SDL_SCANCODE_LSHIFT) 
		|| InputManager::instance().key_still_down(SDL_SCANCODE_RSHIFT)) speed_multiplier = 2;

	// Arrows
	if (InputManager::instance().key_still_down(SDL_SCANCODE_LEFT)
		|| InputManager::instance().key_still_down(SDL_SCANCODE_A)) x -= entity()->base_speed() * speed_multiplier;
	if (InputManager::instance().key_still_down(SDL_SCANCODE_RIGHT)
		|| InputManager::instance().key_still_down(SDL_SCANCODE_D)) x += entity()->base_speed() * speed_multiplier;

	//if (InputManager::instance().key_still_down(SDL_SCANCODE_UP)) y -= entity()->base_speed * speed_multiplier;
	//if (InputManager::instance().key_still_down(SDL_SCANCODE_DOWN)) y += entity()->base_speed * speed_multiplier;

	// Set position according to momentum
	entity()->velocity.set_x(x);
	entity()->velocity.set_y(y);
	entity()->position += entity()->velocity;
}
