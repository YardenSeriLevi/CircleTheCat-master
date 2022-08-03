#pragma once

#include <string>
#include <SFML/Graphics.hpp>

const int BOARD_LEN = 11;

// general data
const unsigned int NUM_OF_LEVELS = 3;
const unsigned int NUM_OF_SOUNDS = 4;
const unsigned int NUM_OF_BACKGROUNDS = 5;
const unsigned int CIRCLE_RADIUS = 30;
const unsigned int EVEN_DISTANCE = 120;
const unsigned int ODD_DISTANCE = 90;
const int CIRCLE_DISTANCE = 68;
const int COLORD_CIRCLES = 14; 


const sf::Color BASE_COLOR = sf::Color(250, 235, 215, 255);
const sf::Color CLICKED_COLOR = sf::Color(188, 143, 143, 255);

//volume data
const unsigned int VOLUME_BG = 5;
const unsigned int VOLUME_WIN_LOSE = 7;

// window data
const int MAX_HEIGHT = 12;
const int MAX_WIDTH = 27;
const int WINDOW_WIDTH = 1100;
const int WINDOW_HEIGHT = 920;

//time data
const int WIN_WIAT = 2000;

// for the status bar
const sf::Color STATUS_BAR_COLOR = sf::Color(153, 153, 255, 255);
const int STATUS_BAR_HEIGHT = 200;
const int STATUS_BAR_CHAR_SIZE = 45;
const float STATUS_BAR_OUTLINE_THICKNESS = 3.0;
const int BUFF_DISTANCE = 60;
const sf::Vector2f HEADLINE_POS = { 200, 10 };
const sf::Vector2f CURR_CLICKS_POS = { 900, 300 };
const sf::Vector2f LEVEL_POS = { 900, 200 };
const sf::Vector2f MUSIC_BUTTON_POS = { 870,  40 };
const sf::Vector2f RESET_BUTTON_POS = { 1030, 40 };
const sf::Vector2f UNDO_BUTTON_POS = { 950, 40 };
const sf::Vector2f WIN_LOSE_POS = { 270, 400 };
const sf::Vector2f DISAPPEAR_POS = { -100, -100 };
const int HALF_BOARD_DIS = (BOARD_LEN / 2) * CIRCLE_DISTANCE;
const sf::Vector2f CAT_START_POS= { EVEN_DISTANCE+ HALF_BOARD_DIS, 150+ HALF_BOARD_DIS };

const sf::Vector2f BUTTONS_SCALE = { 0.08f, 0.08f };
const sf::Vector2f MOVING_OBJ_SCALE = { 0.1f, 0.1f };



//direction data
const sf::Vector2i EVEN_DVec[] = {{0,-1}, {0,1}, {-1,-1}, {-1,0},{1,-1},{1,0}};
const sf::Vector2i ODD_DVec[] =  {{0,-1}, {0,1} ,{-1,0}, {-1,1}, {1,0}, {1,1}};


enum icons
{
	CAT,
	EMPTY
};
enum sounds
{
	S_WIN_LEVEL, S_LOSE_LEVEL, S_WIN_GAME, S_BACKROUND
};

enum backgroundsType
{
	GAME_BACKGROUND, WIN_LEVEL_BACKGROUND,
	WIN_GAME_BACKGROUND
};


enum direction
{
	LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT
};

