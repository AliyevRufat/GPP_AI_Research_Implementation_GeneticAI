#pragma once
#include "Vector2f.h"
#include <vector>
#include "utils.h"
#include <random>
#include <iostream>
#include <iomanip>

class AIGenetics
{
public:

	AIGenetics(int size);
	//Functions
	AIGenetics CopyData() const;
	void MutateNextGen(float alteredMutationRate);
	//Datamembers
	std::vector<Vector2f> m_Directions;
	int m_AmountOfMoves;
};
