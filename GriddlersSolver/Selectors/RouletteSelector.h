#pragma once

#include "./Selector.h"
#include "../RandomGenerator.h"

class RouletteSelector : Selector
{
private:
	double sum_pop_finess; //sum_pop_finess is shifted
	double shift;

public:
	RouletteSelector(const Population& _population, const Estimator& _estimator);
	
	virtual const SolutionCandidate& Next() override;
	using Selector::getPopulationScore;
};