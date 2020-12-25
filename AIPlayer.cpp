#include "pch.h"
#include "AIPlayer.h"

#pragma once
#include "Vector2f.h"
#include "AIGenetics.h"
#include <algorithm>
#include "utils.h"
#include "Obstacles.h"

AIPlayer::AIPlayer()
	:m_Genes{ 700 }
	, m_IsBestPlayer{ false }
	, m_IsDead{ false }
	, m_HasReachedGoal{ false }
	, m_Performance{}
	, m_Pos{}
	, m_Vel{}
	, m_Acc{}
	, m_Size{ 5.0f }
	, m_Goal{}
	, m_IsObstacleWall{}
{
	//starting pos
	m_Pos = Vector2f(100.0f, 280.0f);
	m_Vel = Vector2f(0, 0);
	m_Acc = Vector2f(0, 0);
}

void AIPlayer::Movement()
{
	//add acceleration from list of directions
	if (m_Genes.m_Directions.size() > m_Genes.m_AmountOfMoves)
	{
		m_Acc = m_Genes.m_Directions[m_Genes.m_AmountOfMoves];
		++m_Genes.m_AmountOfMoves;
	}
	else
	{
		m_IsDead = true;
	}
	//move pos
	m_Vel += m_Acc;
	//clamp velocity
	m_Vel.x = Clamp(m_Vel.x, -2.0f, 2.0f);
	m_Vel.y = Clamp(m_Vel.y, -2.0f, 2.0f);
	m_Pos += m_Vel;
}

void AIPlayer::Update(float elapsedSec, const Obstacles& obstacles)
{
	if (!m_IsDead && !m_HasReachedGoal)
	{
		Movement();
		//if out of boundaries
		if (m_Pos.x <= 1 || m_Pos.y <= 1 || m_Pos.x >= 688 || m_Pos.y >= 688)
		{
			m_IsDead = true;
		}
		else if (utils::IsOverlapping(Rectf{ m_Pos.x, m_Pos.y , m_Size ,m_Size }, Rectf{ m_Goal.x ,m_Goal.y , 110.0f, 130.0f })) // if reached the goal
		{
			m_HasReachedGoal = true;
		}
		else if (obstacles.IsOverlappingWithObstacles(Vector2f(m_Pos), m_Size, m_IsObstacleWall)) // if overlapping with any of the obstacles
		{
			if (m_IsObstacleWall)
			{
				m_Vel *= -1.0f;
			}
			else
			{
				m_IsDead = true;
			}
		}
	}
}

void AIPlayer::Draw() const
{
	//draw Ai
	if (m_IsBestPlayer) // draw best player
	{
		if (!m_IsDead)
		{
			glColor4f(0.f, 0.f, 1.f, 1.f);
			utils::DrawRect(m_Pos.x + 10.0f, m_Pos.y + 10.0f, 10.0f, 10.0f, 4.0f);
		}
	}
	else // draw everyone else
	{
		if (!m_IsDead)
		{
			glColor4f(1.f, 0.f, 0.f, 1.f);

			utils::DrawRect(m_Pos.x + 5.0f, m_Pos.y + 5.0f, m_Size, m_Size, 2.0f);
		}
	}
}

void AIPlayer::CalculatePerformance()
{
	float offset = 0.05f;
	if (m_HasReachedGoal) //get performance if reached the goal based on the amount of moves made to optimize the path
	{
		m_Performance = offset + 10000.0f / (float)(m_Genes.m_AmountOfMoves * m_Genes.m_AmountOfMoves);
	}
	else //get performance based on the position of the player
	{
		float distanceToGoal = (float)Distance(m_Goal);
		m_Performance = 1.0f / (distanceToGoal * distanceToGoal);
	}
}

AIPlayer AIPlayer::Breed()
{
	//make clone out of this player
	AIPlayer baby = {};
	baby.m_Genes = m_Genes.CopyData();
	return baby;
}

void AIPlayer::SetGoal(const Vector2f& goal)
{
	m_Goal = goal;
}