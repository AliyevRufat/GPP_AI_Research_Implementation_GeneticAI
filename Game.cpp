#include "pch.h"
#include <iostream>
#include "Game.h"
#include "utils.h"

Game::Game(const Window& window)
	:m_Window{ window }
	, m_Population{ 1500 }
	, m_Goal{ 30.0f, 500.0f }
	, m_Obstacles{}
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	//obstacle
	m_Obstacles.AddObstacle(Vector2f(15.0f, 350.0f), 800.0f, 50);
	//m_Obstacles.AddObstacle(Vector2f(0.0f, 400.0f), 200.0f, 50);
	//m_Obstacles.AddObstacle(Vector2f(355.0f, 350.0f), 350.0f, 50);
}

void Game::Cleanup()
{
}

void Game::Update(float elapsedSec)
{
	m_Population.SetGoal(m_Goal);
	if (m_Population.AllPlayersAreDead())
	{
		m_Population.CalculatePerformance();
		m_Population.Selection();
		m_Population.MutateNextGen();
	}
	else
	{
		m_Population.Update(elapsedSec, m_Obstacles);
	}
}

void Game::Draw() const
{
	ClearBackground();

	m_Obstacles.DrawObstacles();
	//draw ai
	m_Population.Draw();

	//draw m_Goal
	glColor4f(0.f, 1.f, 0.f, 1.f);

	utils::FillRect(m_Goal.x + 20.0f, m_Goal.y + 20.0f, 20.0f, 20.0f);
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_o:
		//m_Obstacles.AddObstacle(Vector2f(40.0f, 250.0f), 350.0f, 50);
		m_Obstacles.AddObstacle(Vector2f(200.0f, 400.0f), 50.0f, 100.0f);
		break;
	case SDLK_p:
		m_Obstacles.AddObstacle(Vector2f(350.0f, 200.0f), 350.0f, 50);
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