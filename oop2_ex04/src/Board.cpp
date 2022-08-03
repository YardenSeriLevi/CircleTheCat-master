
#include "Board.h"

// board c-tor 
Board::Board():
	m_clickCount(0), m_maxColoredCircles(COLORD_CIRCLES), m_winLevel(false),
	m_loseLevel(false), m_restart(false), m_cat(), m_movingCircle(CIRCLE_RADIUS)
{
	setBoard();
}
//------------------------------------------------------
//set the board

void Board::setBoard()
{
	setGrid();
	setLevel();
	setCat();
}
//------------------------------------------------------

void Board::setCat()
{
	m_cat.setPos(CAT_START_POS);
	m_catWay.push_back(m_cat.getPos());

}
//------------------------------------------------------
// draws the grid

void Board::setGrid()
{
	sf::Vector2f pos = { ODD_DISTANCE, 150 };
	for (size_t i = 0; i < BOARD_LEN; i++)
	{
		std::vector<sf::CircleShape> currRow;

		for (size_t j = 0; j < BOARD_LEN; j++)
		{
			sf::CircleShape circle(CIRCLE_RADIUS);

			circle.setPosition(pos);
			circle.setOutlineThickness(2);
			currRow.push_back(circle);
			pos.x += CIRCLE_DISTANCE;
		}
		m_grid.push_back(currRow);
		pos.y += CIRCLE_DISTANCE;
		if (i % 2 == 0) 
			pos.x = EVEN_DISTANCE;
		else 
			pos.x = ODD_DISTANCE;
	}	
}
//------------------------------------------------------
//set level

void Board::setLevel()
{
	m_clickCount = 0;
	ColoringCirclesToBeginningColor();
	UpdatePaintedCircles();
}
//------------------------------------------------------

void Board::SelectRandomColoredCircles()
{
	srand(time(NULL));
	sf::Vector2f pos{ 0,0 };
	int range_row = BOARD_LEN;
	for (int i = 0; i < m_maxColoredCircles; i++)
	{
		do
		{
			pos.x =  rand() % range_row;
			pos.y =  rand() % range_row;
		} while (pos.x == 5 && pos.y == 5);//while its not in the cat place

		m_randomColoredCircles.push_back(pos);
	}
}
//------------------------------------------------------

void Board::ColoringCirclesToBeginningColor()
{
	for (int i = 0; i < BOARD_LEN; i++)
		for (int j = 0; j < BOARD_LEN; j++)
			UnColoringCurrentCircle(i,j);
}
//------------------------------------------------------

void Board::UpdatePaintedCircles()
{
	if (!m_restart)
		SelectRandomColoredCircles();
		
	else
		m_restart = false;

	for (int i = 0; i < m_maxColoredCircles; i++)
		coloringCurrentCircle(m_randomColoredCircles[i].x, m_randomColoredCircles[i].y);
}
//------------------------------------------------------

// draw all the relevent objects 
void Board::draw(sf::RenderWindow& window)const
{
	drawGrid(window);
	m_cat.draw(window);
	window.draw(m_movingCircle);
}
//------------------------------------------------------

// in case the user clicked on the mouse
void Board::mouseButtonReleased(sf::Event event, sf::RenderWindow& window, sf::Time deltaTime)
{
	int x = event.mouseButton.x;
	int y = event.mouseButton.y;

	for (size_t i = 0; i < BOARD_LEN; i++)
		for (size_t j = 0; j < BOARD_LEN; j++)
			if (m_grid[i][j].getFillColor() == BASE_COLOR)
				/* if mouse position is in circle range : pos.x < mouse.x < pos.x+radius and pos.y < mouse.y < pos.y+radius */
				if (x > m_grid[i][j].getPosition().x &&
					x < (m_grid[i][j].getPosition().x + (m_grid[i][j].getRadius() * 2)) &&
					y > m_grid[i][j].getPosition().y &&
					y < (m_grid[i][j].getPosition().y + (m_grid[i][j].getRadius() * 2))&&
					m_grid[i][j].getPosition()!=m_cat.getPos())
				{
					coloringCurrentCircle(i, j);
					doCatStuff( deltaTime);
					m_clickCount++;
					m_clikedCircles.push_back(sf::Vector2f(i, j));
				}
}
//------------------------------------------------------

void Board::mouseButtonMoved(sf::Event event)
{
	auto location = sf::Vector2f(float(event.mouseMove.x), float(event.mouseMove.y));

		for (int i = 0; i < BOARD_LEN; i++) 
			for (int j = 0; j < BOARD_LEN; j++)
				if (m_grid[i][j].getGlobalBounds().contains(location))
				{
					m_movingCircle.setPosition(m_grid[i][j].getPosition());
					m_movingCircle.setOutlineColor(sf::Color::Black);
					m_movingCircle.setFillColor(sf::Color::Transparent);
					m_movingCircle.setOutlineThickness(4);
					break;
				}
			
}
//------------------------------------------------------

void Board::restartLevel()
{
	m_restart = true;
	m_loseLevel = false;
	m_clickCount = 0;
	setLevel();
	setCat();
}
//------------------------------------------------------

void Board::startNewLevel()
{
	m_maxColoredCircles -= 3;
	m_winLevel = false;
	setLevel();
	setCat();
}
//------------------------------------------------------

void Board::undo()
{
	if (m_clickCount > 0)
	{
		takeCatBackToPrevPos();
		sf::Vector2f pos = m_clikedCircles[m_clikedCircles.size()-1];
		m_clikedCircles.pop_back();
		m_clickCount--;
		UnColoringCurrentCircle(pos.x, pos.y);
	}
}
//------------------------------------------------------

void Board::UnColoringCurrentCircle(int x, int y)
{
	m_grid[x][y].setFillColor(BASE_COLOR);
	m_grid[x][y].setOutlineColor(CLICKED_COLOR);
}
//------------------------------------------------------

void Board::coloringCurrentCircle(int x, int y)
{
	m_grid[x][y].setFillColor(CLICKED_COLOR);
	m_grid[x][y].setOutlineColor(BASE_COLOR);
}
//------------------------------------------------------

void Board::drawGrid(sf::RenderWindow& window)const
{
	for (auto i : m_grid)
		for (auto j : i)
			window.draw(j);
}
//------------------------------------------------------

void Board::takeCatBackToPrevPos()
{
	m_catWay.pop_back();
	m_cat.setPos(m_catWay[m_catWay.size() - 1]);
}
//------------------------------------------------------

void Board::doCatStuff(sf::Time& deltaTime)
{
	m_cat.move(m_grid, deltaTime);

	if (m_cat.reachedTheExit())
	{
		m_loseLevel = true;
		m_cat.setPos(DISAPPEAR_POS);
		m_cat.resetReachedTheExit();
	}

	if (m_cat.trapped())
	{
		m_winLevel = true;
		m_cat.resetTrapped();
	}

	m_catWay.push_back(m_cat.getPos());
}
