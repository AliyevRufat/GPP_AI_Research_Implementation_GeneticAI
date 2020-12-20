#include "pch.h"
#include "AIPopulationManager.h"

AIPopulationManager::AIPopulationManager(int populationSize)
	:m_Players{}
	, m_OldGenPlayers{}
	, m_NrOfGeneration{}
	, m_MinAmountOfMoves{ 400 }
	, m_MutationRate{ 0.01f }
{
	//pass the given size
	m_Players.resize(populationSize);
	//zero init every player
	for (size_t i = 0; i < populationSize; i++)
	{
		m_Players[i] = {};
	}
}

void AIPopulationManager::Draw() const
{
	//draw every player
	for (size_t i = 1; i < m_Players.size(); i++)
	{
		m_Players[i].Draw();
	}
	//draw the first and the best performanced player which is indicated with different coloe
	m_Players[0].Draw();
}

void AIPopulationManager::Update(float elapsedSec, const Obstacles& obstacles)
{
	for (size_t i = 0; i < m_Players.size(); i++)
	{
		//kill players that use more amount of moves than the previous best result so that they don't breed for next gen
		if (m_Players[i].m_Genes.m_AmountOfMoves > m_MinAmountOfMoves)
		{
			m_Players[i].m_IsDead = true;
		}
		else
		{
			m_Players[i].Update(elapsedSec, obstacles);
		}
	}
}

void AIPopulationManager::CalculatePerformance()
{
	std::for_each(m_Players.begin(), m_Players.end(), [&](AIPlayer& a) { a.CalculatePerformance(); });
}

bool AIPopulationManager::AllPlayersAreDead()
{
	//find for alive players and players that haven't reached the goal
	auto it = std::find_if(m_Players.begin(), m_Players.end(), [&](AIPlayer& a)
	{
		return (!a.m_IsDead && !a.m_HasReachedGoal);
	});
	//if found return false
	if (it != m_Players.end())
	{
		return false;
	}
	return true;
}

void AIPopulationManager::Selection()
{
	//select parent with the best performance
	AIPlayer bestParent = SelectBestParent();
	//save old gen before changing it
	m_OldGenPlayers = m_Players;
	//make a new player
	std::vector<AIPlayer> nextGenPlayers;
	nextGenPlayers.resize(m_Players.size());
	//make the first element the child of the best player of previous generation
	nextGenPlayers[0] = bestParent.Breed();
	nextGenPlayers[0].m_IsBestPlayer = true;

	for (size_t i = 1; i < nextGenPlayers.size(); i++)
	{
		//breed the best parent
		nextGenPlayers[i] = bestParent.Breed();
	}
	//replace the new list with the original list
	m_Players = nextGenPlayers;
	//
	++m_NrOfGeneration;
	std::cout << m_NrOfGeneration << '\n';
}

AIPlayer AIPopulationManager::SelectBestParent()
{
	AIPlayer bestParent = {};
	float bestFitness = {};
	//get the parent with the best performance
	std::for_each(m_Players.begin(), m_Players.end(), [&](AIPlayer& a) { if (a.m_Performance > bestFitness) { bestFitness = a.m_Performance; bestParent = a; } });
	//get the amount of moves the best parent made if it reached the goal
	if (bestParent.m_HasReachedGoal)
	{
		m_MinAmountOfMoves = bestParent.m_Genes.m_AmountOfMoves;
	}
	//
	return bestParent;
}

void AIPopulationManager::MutateNextGen()
{
	//check if any of the players of previous generation has reached the goal
	auto it = std::find_if(m_OldGenPlayers.begin(), m_OldGenPlayers.end(), [&](AIPlayer& a) {return a.m_HasReachedGoal; });
	//
	if (it != m_OldGenPlayers.end()) // if yes ,then don't increase the mutation rate
	{
		m_MutationRate = 0.01f;
	}
	else // if no, then increase the mutation rate to randomize the directions more often to get to target
	{
		if (m_MutationRate < 0.1f)
		{
			m_MutationRate += 0.01f;
		}
	}
	//
	std::for_each(m_Players.begin() + 1, m_Players.end(), [&](AIPlayer& a) { a.m_Genes.MutateNextGen(m_MutationRate); });
}

void AIPopulationManager::SetGoal(const Vector2f& goal)
{
	std::for_each(m_Players.begin(), m_Players.end(), [&](AIPlayer& a) {a.SetGoal(goal); });
}