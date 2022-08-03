
#include "Controller.h"
using std::cout;

Controller::Controller()
	:m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		"Circle The Cat!", sf::Style::Titlebar | sf::Style::Close)
	, m_playButton(true)
{
	//m_window.setFramerateLimit(15);

	m_backGroundMusic.setBuffer(*FileManager::p2FileManager().getSound(S_BACKROUND));
	m_background.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT + STATUS_BAR_HEIGHT });
	m_background.setTexture(FileManager::p2FileManager().getBackGround(GAME_BACKGROUND));
}
//-----------------------------------------------------------------
//run

void Controller::run()
{
	int levCount = 1;
	m_backGroundMusic.play();
	m_backGroundMusic.setLoop(true);
	m_backGroundMusic.setVolume(VOLUME_BG);

	while (m_window.isOpen())
	{
		m_window.clear(sf::Color(255, 240, 245, 255));
		m_window.draw(m_background);
		m_statusBar.draw(m_window, m_board.getClickCount(),m_board.getWinLevel());
		m_board.draw(m_window);

		sf::Event event;

		while (m_window.pollEvent(event))
			CheckOutWhatEvent( event);
		m_window.display();

		if (m_board.getWinLevel())
		{
			if (levCount < NUM_OF_LEVELS)
			{
				winLevelScreen();
				m_board.startNewLevel();
				levCount++;
				m_statusBar.setLevel(levCount);
			}
			else
				endGame();
		}
		if (m_board.getLoseLevel())
		{
			loseLevelScreen();
			m_board.restartLevel();
		}
	}
}
//-----------------------------------------------------------------
//check event

void Controller::CheckOutWhatEvent( sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::Closed:
		m_window.close();
		break;
	case sf::Event::MouseButtonReleased:
		handelMouseButtonReleased(event);
		break;
	case sf::Event::MouseMoved:
		m_board.mouseButtonMoved(event);
		break;
		
	}
}
//----------------------------------------------
//handle the event that occurred when the MouseButtonReleased

void Controller::handelMouseButtonReleased(sf::Event event)
{
	if (m_statusBar.containsMusicIcon(event))
		handelMusicButtonReleased();
	else if (m_statusBar.containsRestartIcon(event))
		m_board.restartLevel();
	else if (m_statusBar.containsUndoIcon(event))
		m_board.undo();
	else
		m_board.mouseButtonReleased(event, m_window, m_gameClock.restart());
}
//----------------------------------------------
//stopping or playing background music

void Controller::handelMusicButtonReleased()
{
	if (m_backGroundMusic.getStatus() == sf::SoundSource::Status::Playing)
	{
		m_backGroundMusic.stop();
		m_statusBar.setMusicIcon(false);
	}
	else
	{
		m_backGroundMusic.play();
		m_statusBar.setMusicIcon(true);
	}
}
//----------------------------------------------
//show win game msg and close the game

void Controller::endGame()
{
	winGameScreen();
	m_window.close();
}
//---------------------------------------------
//set the win game screen

void Controller::winGameScreen()
{
	m_board.draw(m_window);
	m_window.clear(sf::Color::White);
	sf::RectangleShape background;
	background.setSize({ WINDOW_WIDTH, WINDOW_HEIGHT + STATUS_BAR_HEIGHT });
	background.setTexture(FileManager::p2FileManager().getBackGround(WIN_GAME_BACKGROUND));
	m_window.draw(background);
	m_backGroundMusic.stop();
	setWinSound( S_WIN_GAME);
}
//---------------------------------------------
//set the win level screen

void Controller::winLevelScreen()
{
	m_board.draw(m_window);
	m_statusBar.drawWin(m_window);
	setWinSound(S_WIN_LEVEL);
}
//---------------------------------------------
//set the win level screen

void Controller::loseLevelScreen()
{
	m_board.draw(m_window);
	m_statusBar.drawLose(m_window);
	setWinSound( S_LOSE_LEVEL);
}
//---------------------------------------------------------
//set the relevant wining screen

void Controller::setWinSound(sounds soundType)
{
	sf::Sound effect;
	effect.setBuffer(*FileManager::p2FileManager().getSound(soundType));
	effect.setVolume(VOLUME_WIN_LOSE);
	effect.play();

	m_window.display();
	this_thread::sleep_for(std::chrono::milliseconds(WIN_WIAT));
	
}