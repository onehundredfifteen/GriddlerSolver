#pragma once

#include <map>
#include "./Selector.h"

template<int K>
class BestOfSelector : Selector
{
public:
	BestOfSelector(Population& _population, const Estimator& _estimator);

	virtual SolutionCandidate& Next() override;

	virtual const Scores& getPopulationScore() override;

private:
	double cachedFitness(int a);

protected:
	int element_counter;
	std::map<int, double> known_fitness;
};
