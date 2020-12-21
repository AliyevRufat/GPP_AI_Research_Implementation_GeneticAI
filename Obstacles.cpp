#include "pch.h"
#include "Obstacles.h"
#include <iostream>

Obstacles::Obstacles()
	:m_PosVec{}
	, m_OriginalPosVec{}
	, m_WidthVec{}
	, m_HeightVec{}
	, m_IsMovingVec{}
	, m_MoveDistanceVec{}
	, m_MoveUpVec{ false }
{
}

void Obstacles::AddObstacle(const Vector2f& pos, float width, float height, bool isMoving, float moveDistance, bool moveUp, bool isWall)
{
	m_PosVec.push_back(pos);
	m_OriginalPosVec.push_back(pos);
	m_WidthVec.push_back(width);
	m_HeightVec.push_back(height);
	m_IsMovingVec.push_back(isMoving);
	m_MoveDistanceVec.push_back(moveDistance);
	m_MoveUpVec.push_back(moveUp);
	m_IsWallVec.push_back(isWall);
}

bool Obstacles::IsOverlappingWithObstacles(const Vector2f& playerPos, const float playerSize, bool& isWall) const
{
	//return true if playerpos overlaps with any of the obstacles
	for (size_t i = 0; i < m_PosVec.size(); i++)
	{
		if (utils::IsOverlapping(Rectf(m_PosVec[i].x, m_PosVec[i].y, m_WidthVec[i], m_HeightVec[i]), Rectf(playerPos.x, playerPos.y, playerSize, playerSize)))
		{
			if (m_IsWallVec[i])
			{
				isWall = true;
			}
			else
			{
				isWall = false;
			}
			return true;
		}
	}
	return false;
}

void Obstacles::DrawObstacles() const
{
	//draw every obstacle
	glColor4f(0.f, 0.5f, 0.6f, 1.f);
	//
	int index = 0;
	std::for_each(m_PosVec.begin(), m_PosVec.end(), [&](const Vector2f& a) {utils::FillRect(a.x, a.y, m_WidthVec[index], m_HeightVec[index]); ++index; });
}

void Obstacles::Update(float elapsedSec)
{
	const int moveSpeed = 500;
	for (size_t i = 0; i < m_PosVec.size(); i++)
	{
		if (m_IsMovingVec[i])
		{
			//move left and right with given distance
			if (m_PosVec[i].y >= m_OriginalPosVec[i].y + m_MoveDistanceVec[i])
			{
				m_MoveUpVec[i] = true;
			}
			if (m_PosVec[i].y <= m_OriginalPosVec[i].y - m_MoveDistanceVec[i])
			{
				m_MoveUpVec[i] = false;
			}
			if (m_MoveUpVec[i])
			{
				m_PosVec[i].y = m_PosVec[i].y - (elapsedSec * moveSpeed);
			}
			else
			{
				m_PosVec[i].y = m_PosVec[i].y + (elapsedSec * moveSpeed);
			}
		}
	}
}

void Obstacles::ClearObstacles()
{
	m_PosVec.clear();
	m_OriginalPosVec.clear();
	m_WidthVec.clear();
	m_HeightVec.clear();
	m_IsMovingVec.clear();
	m_MoveUpVec.clear();
	m_MoveDistanceVec.clear();
}