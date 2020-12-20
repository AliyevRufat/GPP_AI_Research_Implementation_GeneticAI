#include "pch.h"
#include "Obstacles.h"

Obstacles::Obstacles()
	:m_Pos{}
	, m_Width{}
	, m_Height{}
{
}

void Obstacles::AddObstacle(const Vector2f& pos, float width, float height)
{
	m_Pos.push_back(pos);
	m_Width.push_back(width);
	m_Height.push_back(height);
}

bool Obstacles::IsOverlappingWithObstacles(const Vector2f& playerPos, const float playerSize) const
{
	//return true if playerpos overlaps with any of the obstacles
	for (size_t i = 0; i < m_Pos.size(); i++)
	{
		if (utils::IsOverlapping(Rectf(m_Pos[i].x, m_Pos[i].y, m_Width[i], m_Height[i]), Rectf(playerPos.x, playerPos.y, playerSize, playerSize)))
		{
			return true;
		}
	}
	return false;
}

void Obstacles::DrawObstacles() const
{
	//draw every obstacle
	glColor4f(0.f, 0.f, 0.f, 1.f);
	//
	int index = 0;
	std::for_each(m_Pos.begin(), m_Pos.end(), [&](const Vector2f& a) {utils::FillRect(a.x, a.y, m_Width[index], m_Height[index]); ++index; });
}