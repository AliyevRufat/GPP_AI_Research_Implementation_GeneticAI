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
	void AddObstacle(const Vector2f& pos, float width, float height, bool isMoving, float moveDistance, bool moveUp = 0, bool isWall = 0);
	bool IsOverlappingWithObstacles(const Vector2f& playerPos, const float playerSize, bool& isWall) const;
	void DrawObstacles() const;
	void Update(float elapsedSec);
	void ClearObstacles();
private:
	//Datamembers
	std::vector<Vector2f> m_PosVec;
	std::vector<Vector2f> m_OriginalPosVec;
	std::vector<float> m_WidthVec, m_HeightVec;
	std::vector<bool> m_IsMovingVec;
	std::vector<bool> m_MoveUpVec;
	std::vector<bool> m_IsWallVec;
	std::vector<float> m_MoveDistanceVec;
};
