#ifndef TEXTMANAGER
#define TEXTMANAGER

namespace game
{
	class TextManager
	{
	public:
		static TextManager& instance();

		// Disable assignemant operators
		TextManager(TextManager const&) = delete;
		TextManager& operator=(TextManager const&) = delete;

		void score_text() const;
		void game_center_text(const char* text) const;
		void increment_score();

	private:
		explicit TextManager();

		int score_;
		bool init();
	};
}

#endif
