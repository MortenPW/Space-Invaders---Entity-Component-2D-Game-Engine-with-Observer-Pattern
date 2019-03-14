#include <iostream>
#include "InputManager.h"
#include "GameManager.h"


game::InputManager& game::InputManager::instance()
{
	/// Automatically thread-safe since C++11 (object initialization will be made only by one thread)
	static InputManager instance;
	return instance;
}

game::InputManager::InputManager()
	: keys_(nullptr)
{
	// Get pointer to SDLs internal key array: SDL_GetKeyboardState
	keys_ = SDL_GetKeyboardState(&key_count_);
	old_keys_ = std::unique_ptr<Uint8>(new Uint8[key_count_]);
}

SDL_Event game::InputManager::event() const
{
	return event_;
}

bool game::InputManager::key_down(const int key_index) const
{
	return (is_key_down(key_index)) && (!was_key_down(key_index));
}

bool game::InputManager::key_still_down(const int key_index) const
{
	return (is_key_down(key_index)) && (was_key_down(key_index));
}

bool game::InputManager::key_up(const int key_index) const
{
	return (!is_key_down(key_index)) && (was_key_down(key_index));
}

bool game::InputManager::key_still_up(const int key_index) const
{
	return (!is_key_down(key_index)) && (!was_key_down(key_index));
}

bool game::InputManager::mouse_down(const int button_index) const
{
	return (is_mouse_down(button_index)) && (!was_mouse_down(button_index));
}

bool game::InputManager::mouse_still_down(const int button_index) const
{
	return (is_mouse_down(button_index)) && (was_mouse_down(button_index));
}

bool game::InputManager::mouse_up(const int button_index) const
{
	return (!is_mouse_down(button_index)) && (was_mouse_down(button_index));
}

bool game::InputManager::mouse_still_up(const int button_index) const
{
	return (!is_mouse_down(button_index)) && (!was_mouse_down(button_index));
}

void game::InputManager::update()
{
	// Store old values
	old_buttons_ = buttons_;
	memcpy(old_keys_.get(), keys_, key_count_ * sizeof(Uint8));

	// Get new values
	SDL_PumpEvents();
	buttons_ = SDL_GetRelativeMouseState(&mouse_x_, &mouse_y_);

	// Get events for event pump
	//SDL_PollEvent(&event_); // TODO: ikke nødvendigvis i bruk akkurat nå....

	// Check states
	control_states();
	event_states();
}

// State snapshot checks
void game::InputManager::control_states() const
{
	// Escape
	if (key_down(SDL_SCANCODE_ESCAPE))
	{
		GameManager::instance().set_ended_game(true);
	}
}

// Event-pump checks
void game::InputManager::event_states() const
{
	// Check if user clicked (X) in window
	if (SDL_HasEvent(SDL_QUIT))
	{
		GameManager::instance().set_ended_game(true);
	}
}

bool game::InputManager::is_key_down(const int key_index) const
{
	return keys_[key_index];
}

bool game::InputManager::was_key_down(const int key_index) const
{
	return old_keys_.get()[key_index];
}

bool game::InputManager::is_mouse_down(const int button_index) const
{
	return buttons_ == button_index;
}

bool game::InputManager::was_mouse_down(const int button_index) const
{
	return old_buttons_ == button_index;
}
