#pragma once

#include "../types.h"
#include "../SolutionCandidate.h"
#include "../Estimators/Estimator.h"

class Selector
{
public:
	Selector(Population& _population, const Estimator& _estimator)
		: population(_population), estimator(_estimator)
	{}
	
	virtual SolutionCandidate& Next() = 0;

protected:
	Population &population;
	const Estimator &estimator;
};