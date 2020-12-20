#pragma once
#include "Vector2f.h"
#include "utils.h"
#include <vector>
#include <algorithm>

class Obstacles
{
public:
	Obstacles();
	//Functions
	void AddObstacle(const Vector2f& pos, float width, float height);
	bool IsOverlappingWithObstacles(const Vector2f& playerPos, const float playerSize) const;
	void DrawObstacles() const;

private:
	//Datamembers
	std::vector<Vector2f> m_Pos;
	std::vector<float> m_Width, m_Height;
};
