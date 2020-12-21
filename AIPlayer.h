#pragma once
#include "Vector2f.h"
#include "AIGenetics.h"
#include <algorithm>
#include "utils.h"
#include "Obstacles.h"

class AIPlayer
{
public:

	AIPlayer();
	//Functions
	void Movement();
	void Update(float elapsedSec, const Obstacles& obstacles);
	void Draw() const;
	void CalculatePerformance();
	AIPlayer Breed();
	void SetGoal(const Vector2f& goal);
	//Helper functions for math
	float Clamp(float x, float a, float b) { return x < a ? a : (x > b ? b : x); }

	double Distance(const Vector2f& aPoint) const
	{
		const double x_diff = (double)m_Pos.x - (double)aPoint.x;
		const double y_diff = (double)m_Pos.y - (double)aPoint.y;
		return std::sqrt(x_diff * x_diff + y_diff * y_diff);
	}
	//Datamembers
	bool m_IsDead = false;
	Vector2f m_Pos;
	AIGenetics m_Genes;
	float m_Performance;
	bool m_HasReachedGoal;
	bool m_IsBestPlayer;

private:
	Vector2f m_Vel;
	Vector2f m_Acc;
	Vector2f m_Goal;
	float m_Size;
	bool m_IsObstacleWall;
};
