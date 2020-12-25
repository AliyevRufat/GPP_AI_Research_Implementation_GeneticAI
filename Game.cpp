#include "pch.h"
#include <iostream>
#include "Game.h"
#include "utils.h"

Game::Game(const Window& window)
	:m_Window{ window }
	, m_Population{ 5000 }
	, m_Goal{ 530.0f,230.0f }
	, m_Obstacles{}
	, m_CanStart{ false }
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	//obstacle///
	//m_Obstacles.AddObstacle(Vector2f(350.0f, 350.0f), 100.0f, 50, true, 200.0f); // moving
	//m_Obstacles.AddObstacle(Vector2f(0.0f, 250.0f), 600, 50, false, 0.0f); //straight line
	//m_Obstacles.AddObstacle(Vector2f(0.0f, 350.0f), 200.0f, 50, false, 0.0f);
	//m_Obstacles.AddObstacle(Vector2f(0.0f, 350.0f), 200.0f, 50, false, 0.0f);
	//m_Obstacles.AddObstacle(Vector2f(355.0f, 350.0f), 350.0f, 50);
	//for (size_t i = 0; i < 9; i++)
	//{
	//	for (size_t j = 0; j < 9; j++)
	//	{
	//		m_Obstacles.AddObstacle(Vector2f(20.0f + j * 100, 20.0f + i * 100), 50.0f, 50.0f, false, 0.0f);
	//	}
	//}
	//m_Obstacles.AddObstacle(Vector2f(120.0f, 20.0f), 50.0f, 50.0f, false, 0.0f);
	//m_Obstacles.AddObstacle(Vector2f(220.0f, 20.0f), 50.0f, 50.0f, false, 0.0f);
	//m_Obstacles.AddObstacle(Vector2f(320.0f, 20.0f), 50.0f, 50.0f, false, 0.0f);
	//m_Obstacles.AddObstacle(Vector2f(420.0f, 20.0f), 50.0f, 50.0f, false, 0.0f);
	//m_Obstacles.AddObstacle(Vector2f(520.0f, 20.0f), 50.0f, 50.0f, false, 0.0f);
	//m_Obstacles.AddObstacle(Vector2f(620.0f, 20.0f), 50.0f, 50.0f, false, 0.0f);
	//m_Obstacles.AddObstacle(Vector2f(720.0f, 20.0f), 50.0f, 50.0f, false, 0.0f);

	//level
	m_Obstacles.AddObstacle(Vector2f(0.0f, 0.0f), 170.0f, 230.0f, false, 0.0f, false, true);
	m_Obstacles.AddObstacle(Vector2f(0.0f, 230.0f), 60.0f, 130.0f, false, 0.0f, false, true);
	m_Obstacles.AddObstacle(Vector2f(0.0f, 360.0f), 170.0f, 700.0f, false, 0.0f, false, true);
	m_Obstacles.AddObstacle(Vector2f(170.0f, 420.0f), 700.0f, 700.0f, false, 0.0f, false, true);
	m_Obstacles.AddObstacle(Vector2f(530.0f, 360.0f), 700.0f, 700.0f, false, 0.0f, false, true);
	m_Obstacles.AddObstacle(Vector2f(640.0f, 230.0f), 700.0f, 700.0f, false, 0.0f, false, true);
	m_Obstacles.AddObstacle(Vector2f(530.0f, 0.0f), 700.0f, 230.0f, false, 0.0f, false, true);
	m_Obstacles.AddObstacle(Vector2f(170.0f, 0.0f), 700.0f, 165.0f, false, 0.0f, false, true);

	//moving enemies
	for (size_t i = 0; i < 13; i++)
	{
		bool moveUp = {};
		if (i % 2 == 0)
		{
			moveUp = true;
		}
		else
		{
			moveUp = false;
		}
		//
		m_Obstacles.AddObstacle(Vector2f(170.0f + i * 30, 285.0f), 15.0f, 15.0f, true, 120.0f, moveUp);
	}
}

void Game::Cleanup()
{
}

void Game::Update(float elapsedSec)
{
	if (m_CanStart)
	{
		m_Population.SetGoal(m_Goal);
		//
		if (m_Population.AllPlayersAreDead())
		{
			//next gen
			m_Population.CalculatePerformance();
			m_Population.Selection();
			m_Population.MutateNextGen();
			//clear and initialize the obstacles
			m_Obstacles.ClearObstacles();
			Initialize();
		}
		else
		{
			m_Population.Update(elapsedSec, m_Obstacles);
		}
		//
		m_Obstacles.Update(elapsedSec);
	}
	//if reached the goal
	if (m_Population.HasReachedTheGoal())
	{
		std::cout << "REACHED THE GOAL" << '\n';
	}
}

void Game::Draw() const
{
	ClearBackground();
	//
	DrawLevel();
	//
	m_Obstacles.DrawObstacles();
	//draw ai
	m_Population.Draw();

	//draw m_Goal
	glColor4f(0.f, 1.f, 0.f, 1.f);

	utils::FillRect(m_Goal.x, m_Goal.y, 110.0f, 130.0f);
}

void Game::DrawLevel() const
{
	glColor4f(0.f, 1.f, 0.f, 1.0f);
	//start pos
	utils::FillRect(Rectf{ 60.0f,230.0f,110.0f,130.0f });
	utils::DrawRect(Rectf{ 60.0f,230.0f,110.0f,130.0f });
	//goal pos
	utils::FillRect(Rectf{ 530.0f,230.0f,110.0f,130.0f });
	utils::DrawRect(Rectf{ 530.0f,230.0f,110.0f,130.0f });
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_o:
		//m_Obstacles.AddObstacle(Vector2f(40.0f, 250.0f), 350.0f, 50);
		//m_Obstacles.AddObstacle(Vector2f(200.0f, 400.0f), 50.0f, 100.0f);
		//m_Obstacles.AddObstacle(Vector2f(350.0f, 200.0f), 350.0f, 50);
		break;
	case SDLK_p:
		m_CanStart = true;
		break;
	}
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
}

void Game::ClearBackground() const
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}