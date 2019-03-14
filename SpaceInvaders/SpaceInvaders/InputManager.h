#ifndef INPUTMANAGER
#define INPUTMANAGER

#include <memory>
#include <SDL.h>

namespace game
{
	class InputManager
	{
	public:
		static InputManager& instance();

		// Disable assignemant operators
		InputManager(InputManager const&) = delete;
		InputManager& operator=(InputManager const&) = delete;

		// Event states
		SDL_Event event() const;

		// Keyboard
		bool key_down(int key_index) const;
		bool key_still_down(int key_index) const;
		bool key_up(int key_index) const;
		bool key_still_up(int key_index) const;

		// Mouse
		bool mouse_down(int button_index) const;
		bool mouse_still_down(int button_index) const;
		bool mouse_up(int button_index) const;
		bool mouse_still_up(int button_index) const;

		void update();

	protected:
		// Meyers' Singleton pattern
		explicit InputManager();

		void control_states() const;
		void event_states() const;

		// Inline helper functions to check key arrays and buttons (is = current frame, was = previous frame)
		bool is_key_down(int key_index) const;
		bool was_key_down(int key_index) const;

		bool is_mouse_down(int button_index) const;
		bool was_mouse_down(int button_index) const;

		SDL_Event event_;

		// A pointer to SDL's internal key state array.
		// (Memory handled by SDL.) 
		const Uint8* keys_;
		int key_count_{};

		// Our own copy of last update's array. 
		// NB! Memory handled dynamically by us! 
		std::unique_ptr<Uint8> old_keys_;

		// Mouse pos x and y.
		int mouse_x_{};
		int mouse_y_{};

		// Mouse buttons pressed. 
		Uint8 buttons_{};

		// Mouse buttons pressed last update.
		Uint8 old_buttons_{};
	};
}

#endif
