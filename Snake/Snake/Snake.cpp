#include "Snake.h"

Snake::Snake(int startX, int startY)
{
	std::vector<int> piece;
	piece.push_back(startX);
	piece.push_back(startY);
	body.push_back(piece);
	directions.push_back(0);
}

int Snake::getHeadX()
{
	return body[0][0];
}

int Snake::getHeadY()
{
	return body[0][1];
}

std::vector<std::vector<int>> Snake::getBody()
{
	return body;
}

void Snake::grow()
{
	int dir = directions[directions.size() - 1];
	std::vector<int> tail = body[body.size() - 1];
	if (dir == 0)
	{
		tail[1] -= 1;
	}
	else if (dir == 1)
	{
		tail[1] += 1;
	}
	else if (dir == 2)
	{
		tail[0] -= 1;
	}
	else
	{
		tail[0] += 1;
	}
	directions.push_back(dir);
	body.push_back(tail);

}

void Snake::UpdateBody(int dir)
{
	directions.insert(directions.begin(),dir);
	directions.pop_back();
	for (int i = 0; i < body.size(); i++)
	{
		if (directions[i] == 0)
		{
			body[i][1] += 1;
		}
		else if (directions[i] == 1)
		{
			body[i][1] -= 1;
		}
		else if (directions[i] == 2)
		{
			body[i][0] += 1;
		}
		else
		{
			body[i][0] -= 1;
		}
	}
}

bool Snake::SelfCollide()
{
	for (int i = 1; i < body.size(); i++)
	{
		if (body[0][0] == body[i][0] && body[0][1] == body[i][1])
		{
			return true;
		}
	}
	return false;
}