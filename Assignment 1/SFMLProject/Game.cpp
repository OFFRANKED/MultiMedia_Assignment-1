#include <Book/Game.hpp>

const float Game::PlayerSpeed = 250.0f;
const sf::Time Game::Frametime = sf::seconds(1.0f / 60.0f);

Game::Game()
#pragma region Step2
	: mWindow(sf::VideoMode(800, 600), "SFML Application", sf::Style::Close)
	, mTexture()
	, mBackground()
	, mPlayer()
	, mTexture2()
	, mPlayer2(sf::Vector2f(60.0f, 5.0f))
	//~~~~~~~~~~~~~~~~~~~~~~~~~Key Functions~~~~~~~~~~~~~~~~
	//, mIsMovingDown(false)
	, mIsMovingLeft(false)
	, mIsMovingRight(false)
	//, mIsMovingUp(false)
	//~~~~~~~~~~~~~~~~~~~~~~~~~Key Functions~~~~~~~~~~~~~~~~
#pragma endregion

{

	mPlayer.setRadius(5.0f);
	mPlayer.setPosition(100.f, 100.f);
	mPlayer.setFillColor(sf::Color::White);
	
	//Text code
	if (!mFont.loadFromFile("Media/Sansation.ttf"))return;
	mText.setFont(mFont);
	
	mText.setPosition(100, 2);
	mText.setCharacterSize(20);
	mText.setFillColor(sf::Color::Black);

	mText2.setFont(mFont);
	mText2.setPosition(400, 2);
	mText2.setCharacterSize(20);
	mText2.setFillColor(sf::Color::Black);


	

	//Extra
	//mStatisticsText.setString("Lives : 03" + toString(i));
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(20, 500);
	mStatisticsText.setCharacterSize(10);
	mStatisticsText.setFillColor(sf::Color::Red);



#pragma region Step3
	//Comment out the following section
	mPlayer2.setPosition(350.f, 590.f);
	//if (!mTexture2.loadFromFile("Media/Textures/Eagle.png"))
		//return;
	//Done By me :-)

	mPlayer2.setFillColor(sf::Color::White);


	if (!mTexture.loadFromFile("Media/Textures/Sky_Blue.png")) 
		return;
	mTexture.setRepeated(true);
	mBackground.setTexture(mTexture);
	// Define a rectangle, located at (0, 0) with a size of 800X600
	//Comment out the following section to see the difference
	mBackground.setTextureRect(sf::IntRect(0, 0, 800, 600));

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~extra stuff~~~~~~~~~~~~~~~~~~~~~~~~
	if (!mIcon.loadFromFile("Media/Textures/icon.png")) return;
	mWindow.setIcon(mIcon.getSize().x, mIcon.getSize().y, mIcon.getPixelsPtr());

	mIcon.create(20, 20, sf::Color::Yellow);
	sf::Color color = mIcon.getPixel(0, 0);
	color.r = 0;
	mIcon.setPixel(0, 0, color);
	mWindow.setIcon(mIcon.getSize().x, mIcon.getSize().y, mIcon.getPixelsPtr());

	//~~~~~~~~~~~~~~~~~~~Music stuff~~~~~~~~~~~~~~~~~
	//if (!mMusic.openFromFile("Media/Textures/nice_music.wav")) return;
	//mMusic.setVolume(100);
	//mMusic.setLoop(true);
	//mMusic.setAttenuation(100);
	//mMusic.setPitch(20);
	//mMusic.play();
	//~~~~~~~~~~~~~~~~~~~Music stuff~~~~~~~~~~~~~~~~~


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~extra stuff ends~~~~~~~~~~~~~~~~~~~~~~
#pragma endregion
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > Frametime)
		{
			timeSinceLastUpdate -= Frametime;
			processEvents();
			update(Frametime);
		}
		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			mWindow.close();
			break;
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		}
	}
}

void Game::update(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingLeft && mPlayer2.getPosition().x>0) movement.x -= PlayerSpeed;
	if (mIsMovingRight && mPlayer2.getPosition().x<741) movement.x += PlayerSpeed;
	//~~~~~~~~~~~~~~~~~~~~~~~~~Extra~~~~~~~~~~~~~~~~~~~~~~~~
	//if (mIsMovingUp) movement.y -= 0.1f;
	//if (mIsMovingDown) movement.y += 0.1f;
	//~~~~~~~~~~~~~~~~~~~~~~~~~Extra~~~~~~~~~~~~~~~~~~~~~~~~
	mPlayer2.move(movement * elapsedTime.asSeconds());
	UpdateLives();
	updateScore();
}

void Game::render()
{
	if (l == 0)
	{
		mWindow.clear();
		mWindow.draw(mBackground);
		mWindow.draw(mText3);
		mWindow.display();
	}
	else {
		mWindow.clear();

#pragma region Step4
		mWindow.draw(mBackground);
		mWindow.draw(mText);
		mWindow.draw(mStatisticsText);
		mWindow.draw(mText2);
		mWindow.draw(mPlayer2);
#pragma endregion
		mWindow.draw(mPlayer);
		mWindow.display();
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (isPressed)
	{
		if (key == sf::Keyboard::A) mIsMovingLeft = true;
		if (key == sf::Keyboard::Q) l--;
		if (key == sf::Keyboard::E) i++;
		//~~~~~~~~~~~~~~~~~~~Extra Stuff~~~~~~~~~~~~~~~~~~
		//else if (key == sf::Keyboard::W) mIsMovingUp = true;
		//else if (key == sf::Keyboard::S) mIsMovingDown = true;
		//~~~~~~~~~~~~~~~~~~~Extra Stuff~~~~~~~~~~~~~~~~~~
		else if (key == sf::Keyboard::D) mIsMovingRight = true;
	}

	if (!isPressed)
	{
		if (key == sf::Keyboard::A) mIsMovingLeft = false;
		else if (key == sf::Keyboard::D) mIsMovingRight = false;
		//~~~~~~~~~~~~~~~~~~~Extra Stuff~~~~~~~~~~~~~~~~~~
		//else if (key == sf::Keyboard::W) mIsMovingUp = false;
		//else if (key == sf::Keyboard::S) mIsMovingDown = false;
		//~~~~~~~~~~~~~~~~~~~Extra Stuff~~~~~~~~~~~~~~~~~~
		
	}
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrame += 1;
	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString("Frame / second = " + toString(mStatisticsNumFrame) + "\n" + "Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrame) + " US ");
		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrame = 0;
	}

}

void Game::updateScore()
{
	mText.setString("Score : " + toString(i));
}

void Game::UpdateLives()
{
	mText2.setString("Lives : " + toString(l));

	mText3.setFont(mFont);
	mText3.setString("Game Over ! \n Score : " + toString(i));
	mText3.setPosition(370, 270);
	mText3.setCharacterSize(30);
	mText3.setFillColor(sf::Color::Black);

}



