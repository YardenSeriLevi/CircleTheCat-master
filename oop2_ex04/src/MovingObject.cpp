#include "MovingObject.h"


//---------------------------------------------------

bool MovingObject::canMove(std::vector<std::vector<sf::CircleShape>> grid, sf::Vector2i source)
{
	if (//can move right
		(grid[source.x][source.y - 1].getFillColor() == BASE_COLOR)
		//can move right
		|| (grid[source.x][source.y + 1].getFillColor() == BASE_COLOR)
		//can move up left
		|| (isLineEven(source.x) && grid[source.x - 1][source.y - 1].getFillColor() == BASE_COLOR)
		|| (!isLineEven(source.x) && grid[source.x - 1][source.y].getFillColor() == BASE_COLOR)
		//can move up right
		|| (isLineEven(source.x) && grid[source.x - 1][source.y].getFillColor() == BASE_COLOR)
		|| (!isLineEven(source.x) && grid[source.x - 1][source.y + 1].getFillColor() == BASE_COLOR)
		//can move down left
		|| (isLineEven(source.x) && grid[source.x + 1][source.y - 1].getFillColor() == BASE_COLOR)
		|| (!isLineEven(source.x) && grid[source.x + 1][source.y].getFillColor() == BASE_COLOR)
		//can move down right
		|| (isLineEven(source.x) && grid[source.x + 1][source.y].getFillColor() == BASE_COLOR)
		|| (!isLineEven(source.x) && grid[source.x + 1][source.y + 1].getFillColor() == BASE_COLOR))
		return true;

	m_trapped = true;
	return false;
}
//---------------------------------------------------

bool MovingObject::isValid(int ind)const
{
	return ind >= 0 && ind < BOARD_LEN;
}
//---------------------------------------------------

bool MovingObject::isLineEven(int line)const
{
	return line % 2 == 0;
	std::cout << line;
}
//---------------------------------------------------
// applying BFS on matrix cells starting from source

sf::Vector2i MovingObject::getNextMove(std::vector<std::vector<sf::CircleShape>> grid, sf::Vector2f objPos)
{
	std::vector<std::vector<sf::Vector2i>> discover;

	bool visited[BOARD_LEN][BOARD_LEN];	// To keep track of visited vertex. Marking
	// blocked cells as visited.
	std::queue<sf::Vector2i > q;
	sf::Vector2i p;

	resetMatrix(discover);
	sf::Vector2i source = fillVisitedAndFindSource(grid, visited, objPos);

	if (winSituation(source))
		return { -1,-1 };

	if (!canMove(grid, source))
		return { -1,-1 };

	q.push(source);
	visited[source.x][source.y] = true;
	while (!q.empty())
	{
		p = q.front();
		q.pop();

		// Destination found
		if (p.x == 0 || p.x == 10 || p.y == 0 || p.y == 10)
		{
			if (source == discover[p.x][p.y])
				return p;
			return calaulateFirstMove(discover, source, discover[p.x][p.y]);
		}

		checkDirection(p + EVEN_DVec[LEFT], visited, q, discover, p);

		checkDirection(p + EVEN_DVec[RIGHT], visited, q, discover, p);

		if (isLineEven(p.x))
			checkDirection(p + EVEN_DVec[UP_LEFT], visited, q, discover, p);
		else
			checkDirection(p + ODD_DVec[UP_LEFT], visited, q, discover, p);

		if (isLineEven(p.x))
			checkDirection(p + EVEN_DVec[UP_RIGHT], visited, q, discover, p);
		else
			checkDirection(p + ODD_DVec[UP_RIGHT], visited, q, discover, p);

		if (isLineEven(p.x))
			checkDirection(p + EVEN_DVec[DOWN_LEFT], visited, q, discover, p);
		else
			checkDirection(p + ODD_DVec[DOWN_LEFT], visited, q, discover, p);

		if (isLineEven(p.x))
			checkDirection(p + EVEN_DVec[DOWN_RIGHT], visited, q, discover, p);
		else
			checkDirection(p + ODD_DVec[DOWN_RIGHT], visited, q, discover, p);
	}
	return moveObjectRandomly(grid, source);
}
//---------------------------------------------------

void MovingObject::checkDirection( sf::Vector2i dir, bool visited[BOARD_LEN][BOARD_LEN],
	std::queue<sf::Vector2i>& q,
	std::vector<std::vector<sf::Vector2i>>& discover, sf::Vector2i p)
{
	if (isValid(dir.y) && isValid(dir.x) && visited[dir.x][dir.y] == false)
	{
		q.push(dir);
		visited[dir.x][dir.y] = true;
		discover[dir.x][dir.y] = sf::Vector2<int>(p.x, p.y);
	}
}
//---------------------------------------------------

void MovingObject::resetMatrix(std::vector<std::vector<sf::Vector2i>>& discover)
{
	for (size_t i = 0; i < BOARD_LEN; i++)
	{
		std::vector<sf::Vector2i> currRow;

		for (size_t j = 0; j < BOARD_LEN; j++)
		{
			currRow.push_back({ -1, -1 });
		}
		discover.push_back(currRow);
	}
}
//---------------------------------------------------

sf::Vector2i MovingObject::fillVisitedAndFindSource(std::vector<std::vector<sf::CircleShape>> grid,
	 bool visited[BOARD_LEN][BOARD_LEN], sf::Vector2f objPos)
{
	sf::Vector2i source = { 0,0 };

	for (int i = 0; i < BOARD_LEN; i++)
	{
		for (int j = 0; j < BOARD_LEN; j++)
		{
			if (grid[i][j].getFillColor() == CLICKED_COLOR)//cant pass them
				visited[i][j] = true;
			else
				visited[i][j] = false;

			// checking if the current place is were the cat standing on
			if (grid[i][j].getPosition() == objPos)
			{
				source.x = i;
				source.y = j;
			}
		}
	}
	return source;
}
//---------------------------------------------------

sf::Vector2i MovingObject::calaulateFirstMove(std::vector<std::vector<sf::Vector2i>> discover,
	sf::Vector2i source, sf::Vector2i foundExit)
{
	sf::Vector2i temp = foundExit,
		firstStep = temp;

	while (temp != source)
	{
		firstStep = temp;
		temp = discover[temp.x][temp.y];
	}
	return firstStep;
}
//---------------------------------------------------

bool MovingObject::winSituation(sf::Vector2i source)
{
	if (source.x == 0 || source.x == 10 || source.y == 0 || source.y == 10)
	{
		m_reachedTheExit = true;
		return true;
	}
	return false;
}
//---------------------------------------------------

sf::Vector2i MovingObject::moveObjectRandomly(std::vector<std::vector<sf::CircleShape>> grid
	, sf::Vector2i source)
{
	bool even = isLineEven(source.x);
	sf::Vector2i pos{ 0,0 };

	do
	{
		pos = grillDirection(even);
	} while (grid[pos.x + source.x][pos.y + source.y].getFillColor() != BASE_COLOR);

	pos += source;
	return pos;
}
//----------------------------------------------------

sf::Vector2i MovingObject::grillDirection(bool even) const
{
	int dir = rand() % 6;
	sf::Vector2i res;

	switch ((direction)dir)
	{
	case LEFT:
		return EVEN_DVec[LEFT];
	case RIGHT:
	    return EVEN_DVec[RIGHT];
	case UP_RIGHT:
		if (even) return EVEN_DVec[UP_RIGHT]; else return ODD_DVec[UP_RIGHT];
	case UP_LEFT:
		if (even) return EVEN_DVec[UP_LEFT]; else return ODD_DVec[UP_LEFT];
	case DOWN_RIGHT:
		if (even) return EVEN_DVec[DOWN_RIGHT]; else return ODD_DVec[DOWN_RIGHT];
	case DOWN_LEFT:
		if (even) return EVEN_DVec[DOWN_LEFT]; else return ODD_DVec[DOWN_LEFT];
	}
	return { 0, 0 };

}
