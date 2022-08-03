#pragma once
#include "StatusBar.h"
#include "FileManager.h"
#include <iostream>


//--------------------------------------------------
//constructor

StatusBar::StatusBar() : m_level(1)
{
	this->m_font = (*(FileManager::p2FileManager().getFont()));
	setHeadlineText();
	setCurrClicksText();
	setLevelText();
	setWinLevelText();
	setLoseLevelText();
	setButtons();
}
//------------------------------------------

void StatusBar::updateLevel(const bool isLevelUp)
{
	if (isLevelUp)
		this->m_level++;

	this->m_levelText.setString("Level :" + std::to_string(this->m_level));
}
//------------------------------------------
void StatusBar::updateClicks(const int numOfClicks)
{
	this->m_currClicksText.setString("Clicks :" + std::to_string(numOfClicks));
}
int StatusBar::getLevel() const
{
	return this->m_level;
}
//------------------------------------------

void StatusBar::setLevel(const int lev)
{
	this->m_level = lev;
}
//------------------------------------------
void StatusBar::draw(sf::RenderWindow& window, const int numOfClicks, const bool isLevelUp)
{
	updateClicks(numOfClicks);
	updateLevel(isLevelUp);

	window.draw(this->m_headlineText);
	window.draw(this->m_currClicksText);
	window.draw(this->m_levelText);
	drawButtons(window);
}
//------------------------------------------

void StatusBar::drawButtons(sf::RenderWindow& window)
{
	window.draw(this->m_musicIcon);
	window.draw(this->m_undoIcon);
	window.draw(this->m_resetIcon);
}
//------------------------------------------

void StatusBar::drawWin(sf::RenderWindow& window)
{
	window.draw(m_winLevelText);
}
//------------------------------------------

void StatusBar::drawLose(sf::RenderWindow& window)
{
	window.draw(m_loseLevelText);
}
//------------------------------------------

void StatusBar::resetNumOfLevel()
{
	m_level = 0;
}
//------------------------------------------

bool StatusBar::containsMusicIcon(const sf::Event& event) const
{
	if (this->m_musicIcon.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
		return true;
	return false;
}
//------------------------------------------

void StatusBar::setMusicIcon(const bool isSoundOn)
{
	this->m_musicIcon.setTexture(*FileManager::p2FileManager().getMusicIcon(isSoundOn));
}
//--------------------------------------------
void StatusBar::setHeadlineText()
{
	this->m_headlineText.setFont(*FileManager::p2FileManager().getFont());
	this->m_headlineText.setCharacterSize(STATUS_BAR_CHAR_SIZE*2);
	this->m_headlineText.setPosition(HEADLINE_POS);
	this->m_headlineText.setColor(STATUS_BAR_COLOR);
	this->m_headlineText.setOutlineColor(sf::Color::White);
	this->m_headlineText.setOutlineThickness(STATUS_BAR_OUTLINE_THICKNESS);
	this->m_headlineText.setString("Circle The Cat");
}
//--------------------------------------------

void StatusBar::setCurrClicksText()
{
	this->m_currClicksText.setFont(*FileManager::p2FileManager().getFont());
	this->m_currClicksText.setCharacterSize(STATUS_BAR_CHAR_SIZE);
	this->m_currClicksText.setPosition(CURR_CLICKS_POS);
	this->m_currClicksText.setColor(STATUS_BAR_COLOR);
	this->m_currClicksText.setOutlineColor(sf::Color(230, 230, 255, 255));
	this->m_currClicksText.setOutlineThickness(STATUS_BAR_OUTLINE_THICKNESS);
}
//--------------------------------------------

void StatusBar::setLevelText()
{
	this->m_levelText.setFont(*FileManager::p2FileManager().getFont());
	this->m_levelText.setCharacterSize(STATUS_BAR_CHAR_SIZE);
	this->m_levelText.setPosition(LEVEL_POS);
	this->m_levelText.setColor(STATUS_BAR_COLOR);
	this->m_levelText.setOutlineColor(sf::Color(230, 230, 255, 255));
	this->m_levelText.setOutlineThickness(STATUS_BAR_OUTLINE_THICKNESS);
}
//--------------------------------------------

void StatusBar::setWinLevelText()
{
	this->m_winLevelText.setFont(*FileManager::p2FileManager().getFont());
	this->m_winLevelText.setCharacterSize(STATUS_BAR_CHAR_SIZE*2);
	this->m_winLevelText.setPosition(WIN_LOSE_POS);
	this->m_winLevelText.setColor(sf::Color::Black);
	this->m_winLevelText.setOutlineColor(sf::Color(230, 230, 255, 255));
	this->m_winLevelText.setOutlineThickness(STATUS_BAR_OUTLINE_THICKNESS);
	this->m_winLevelText.setString("Good Job !");

}
//--------------------------------------------

void StatusBar::setLoseLevelText()
{
	this->m_loseLevelText.setFont(*FileManager::p2FileManager().getFont());
	this->m_loseLevelText.setCharacterSize(STATUS_BAR_CHAR_SIZE*2);
	this->m_loseLevelText.setPosition(WIN_LOSE_POS);
	this->m_loseLevelText.setColor(sf::Color::Black);
	this->m_loseLevelText.setOutlineColor(sf::Color(230, 230, 255, 255));
	this->m_loseLevelText.setOutlineThickness(STATUS_BAR_OUTLINE_THICKNESS);
	this->m_loseLevelText.setString("Try Again !");

}
//--------------------------------------------
void StatusBar::setButtons()
{
	setMusicIcon();
	setUndoIcon();
	setRestartIcon();
}
//--------------------------------------------
void StatusBar::setMusicIcon()
{
	this->m_musicIcon.setTexture(*FileManager::p2FileManager().getMusicIcon(true));
	this->m_musicIcon.setPosition(MUSIC_BUTTON_POS);
	this->m_musicIcon.scale(BUTTONS_SCALE);
}
//--------------------------------------------

void StatusBar::setRestartIcon()
{
	this->m_resetIcon.setTexture(*FileManager::p2FileManager().getRestartIcon());
	this->m_resetIcon.setPosition(RESET_BUTTON_POS);
	this->m_resetIcon.scale(BUTTONS_SCALE);
}
//--------------------------------------------

void StatusBar::setUndoIcon()
{
	this->m_undoIcon.setTexture(*FileManager::p2FileManager().getUndoIcon());
	this->m_undoIcon.setPosition(UNDO_BUTTON_POS);
	this->m_undoIcon.scale(BUTTONS_SCALE);
}
//------------------------------------------

bool StatusBar::containsRestartIcon(const sf::Event& event) const
{
	if (this->m_resetIcon.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
		return true;
	return false;
}
//------------------------------------------

bool StatusBar::containsUndoIcon(const sf::Event& event) const
{
	if (this->m_undoIcon.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
		return true;
	return false;
}