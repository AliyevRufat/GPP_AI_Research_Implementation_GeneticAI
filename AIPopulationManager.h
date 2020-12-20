#pragma once
#include "AIPlayer.h"
#include "Obstacles.h"

class AIPopulationManager
{
public:

	AIPopulationManager(int populationSize);
	//Functions
	void Draw() const;
	void Update(float elapsedSec, const Obstacles& obstacles);
	void CalculatePerformance();
	bool AllPlayersAreDead();
	void Selection();
	AIPlayer SelectBestParent();
	void MutateNextGen();
	void SetGoal(const Vector2f& goal);
private:
	//Datamembers
	std::vector<AIPlayer> m_Players;
	std::vector<AIPlayer> m_OldGenPlayers;
	int m_NrOfGeneration;
	int m_MinAmountOfMoves;
	float m_MutationRate;
};
