#pragma once

#include "../types.h"
#include "../SolutionCandidate.h"
#include "../Estimators/Estimator.h"

class Selector
{
public:
	Selector(Population& _population, const Estimator& _estimator)
		: population(_population), estimator(_estimator), population_score(population.size(), -0.1e+09)
	{}
	
	virtual SolutionCandidate& Next() = 0;

	virtual const Scores& getPopulationScore() {
		return population_score;
	}

protected:
	Population &population;
	const Estimator &estimator;

	Scores population_score;
};