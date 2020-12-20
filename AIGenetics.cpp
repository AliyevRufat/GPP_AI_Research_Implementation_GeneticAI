#include "pch.h"
#include "AIGenetics.h"

AIGenetics::AIGenetics(int size)
	:m_Directions{}
	, m_AmountOfMoves{}
{
	m_Directions.resize(size);
	//get random directions from radian
	for (size_t i = 0; i < m_Directions.size(); i++)
	{
		//random angle
		float randomAngle = 0.0f + (float)(rand()) / ((float)(RAND_MAX / (2 * utils::g_Pi - 0.0f)));
		//make a direction of that angle and put it in the list
		m_Directions[i] = Vector2f(cos(randomAngle), sin(randomAngle));
	}
}

AIGenetics AIGenetics::CopyData() const
{
	//make a clone
	AIGenetics clone(m_Directions.size());
	//get the directions data and store it in clone
	int index = 0;
	std::for_each(m_Directions.begin(), m_Directions.end(), [&](auto& a) { clone.m_Directions[index] = a; ++index; });
	return clone;
}

void AIGenetics::MutateNextGen(float alteredMutationRate)
{
	//chance of mutation
	float mutationRate = alteredMutationRate;
	//mutate if random number is smaller than mutationRate
	for (size_t i = 0; i < m_Directions.size(); i++)
	{
		float randNr = (rand() % 101) / 100.0f;

		if (randNr < mutationRate)
		{
			//get a new angle according to the previous angle and give offset to it
			float oldAngle = acos(m_Directions[i].x);
			float randOffset = -utils::g_Pi + (float)(rand()) / ((float)(RAND_MAX / (utils::g_Pi - -utils::g_Pi)));
			//set the new angle as the new direction
			m_Directions[i] = Vector2f(cos(oldAngle + randOffset), sin(oldAngle + randOffset));
		}
	}
}