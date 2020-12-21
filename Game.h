#pragma once
#include "Vector2f.h"
#include "AIPopulationManager.h"
#include "Obstacles.h"

class Game
{
public:
	explicit Game(const Window& window);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update(float elapsedSec);
	void Draw() const;

	// Event handling
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

private:
	// DATA MEMBERS
	const Window m_Window;
	AIPopulationManager m_Population;
	Vector2f m_Goal;
	Obstacles m_Obstacles;
	bool m_CanStart; // made this variable to press a button and start the algoritm (for screen recording purpose)
	// FUNCTIONS
	void Initialize();
	void Cleanup();
	void ClearBackground() const;
};