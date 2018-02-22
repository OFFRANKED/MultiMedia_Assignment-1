#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Book/StringHelpers.hpp>
//#include <Book/StringHelpers.inl>



class Game : private sf::NonCopyable
{
public:
	Game();
	void					run();


private:
	void					processEvents();
	void					update(sf::Time elapsedTime);
	void					render();
	void					handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void					updateStatistics(sf::Time elapsedTime);
	void					updateScore();
	void					UpdateLives();


private:

	sf::RenderWindow		mWindow;
	sf::CircleShape			mPlayer;

#pragma region Step 1
	sf::Sprite				mBackground;
	sf::Texture				mTexture;
	sf::RectangleShape		mPlayer2;
	sf::Texture				mTexture2;

	sf::Text				mText;
	sf::Text				mText2;
	sf::Font				mFont;
	sf::Text				mText3;
	int						i = 0, Hight=800;
	int						l = 3, Width =600;
	static const float PlayerSpeed;
	static const sf::Time Frametime;
	bool mIsMovingLeft;
	bool mIsMovingRight;
	float p1 = 100.f, p2 = 100.f;

	//~~~~~~~~~~~~~~~~~~~new other stuff~~~~~~~~~~~~~~~~~
	sf::Image				mIcon;
	//sf::Music				mMusic;
	//bool mIsMovingUp;
	//bool mIsMovingDown;
	
	std::size_t				mStatisticsNumFrame;
	sf::Text				mStatisticsText;
	sf::Time				mStatisticsUpdateTime;
	//sf::Event				mKeyPressed;
	//~~~~~~~~~~~~~~~~~~~new other stuff~~~~~~~~~~~~~~~~~
#pragma endregion

};

#endif // BOOK_GAME_HPP
