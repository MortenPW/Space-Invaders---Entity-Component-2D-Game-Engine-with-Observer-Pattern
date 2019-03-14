#ifndef GAMEMANAGER
#define GAMEMANAGER


// TODO: Tatt i bruk et enkelt OOP entity component pattern, pr�vde meg p� DOD, men inns� at det er utenfor hva jeg �nsker � begi meg ut p� n�. 
// TODO: Da hadde jeg heller brukt et �pent kritisert og veltestet bibliotek for h�ndtering av komponenter, fordi ytelsesforskjellen tilsier det, og fordi det er enklere.

/*
* V�r eksplisitt!
*	Const, fordi vi ikke skal endre noe- std::vector, fordi vi skal ha en liste fra standard biblioteket
*	std::unique_ptr fordi vi vil ha en unik peker fra standard biblioteket
*	game::Player, fordi vi vil hente ut en spiller fra spill biblioteket
*	&, fordi listen er en referanse til noe som allerede eksisterer
*
*	game::GameManager::players() er der vi n�r denne koden
*
*	S� bruk alltid eksplisitt deklarering for � v�re tydelig-
*	det er da man virkelig ser- at koden bare er en liten lokasjon, i et st�rre bibliotek
*
*	S� v�r eksplisitt: vi gir ikke funksjonene v�re navn- vi gir dem adresser
*
*	- for hvilke avhengigheter har du?
* 
*		std::vector<std::unique_ptr<game::Player>> const& game::GameManager::players() const
*		{
*			return players_;
*		}
*/

namespace game
{
	class GameManager
	{
	public:
		// Meyers' Singleton pattern
		static GameManager& instance();

		// Disable assignemant operators
		GameManager(const GameManager&) = delete;
		GameManager& operator=(const GameManager&) = delete;

		// Member functions
		bool ended_game() const;
		void set_ended_game(bool ended_game);

		bool game_over() const;
		void set_game_over(bool game_over);
		bool game_won() const;
		void configure_game();
		void game_loop();

	private:
		explicit GameManager();

		void run_updates();

		bool ended_game_;
		bool game_over_;
	};
}

#endif
