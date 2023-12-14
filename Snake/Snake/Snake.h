#pragma once
#include <vector>
class Snake
{
private:
	std::vector<std::vector<int>> body;
	std::vector<int> directions;
public:
	Snake(int startX, int startY);
	int getHeadX();
	int getHeadY();
	void UpdateBody(int dir);
	void grow();
	std::vector<std::vector<int>> getBody();
	bool SelfCollide();
};