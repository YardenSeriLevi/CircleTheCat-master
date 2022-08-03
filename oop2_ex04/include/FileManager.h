#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Macros.h"


class FileManager
{
public:
	~FileManager() {};
	static FileManager& p2FileManager();

	const sf::Texture* getCatTexture()const;
	const sf::SoundBuffer* getSound(sounds)const;
	const sf::Texture* getMusicIcon(bool)const;
	const sf::Texture* getRestartIcon()const;
	const sf::Texture* getUndoIcon()const;
	const sf::Texture* getBackGround(backgroundsType)const;
	const sf::Font* getFont()const;

private:
	FileManager();
	FileManager(const FileManager&) = default;
	FileManager& operator=(const FileManager&) = default;

	void loadFromFileIcons();
	void loadAudio();
	void loadButtons();
	void loadMusicIcon();
	void loadResetIcon();
	void loadUndoIcon();
	void loadBackgrounds();

	sf::Texture m_backgrounds[NUM_OF_BACKGROUNDS];
	sf::Texture m_musicTexture[2];
	sf::Texture m_restartIcon;
	sf::Texture m_catIcon;
	sf::Texture m_undoIcon;
	sf::SoundBuffer m_audio[NUM_OF_SOUNDS];
	sf::Font m_font;
};


