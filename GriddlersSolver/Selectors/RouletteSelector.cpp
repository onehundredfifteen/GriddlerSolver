#include "../stdafx.h"
#include "./RouletteSelector.h"
#include "../RandomGenerator.h"

RouletteSelector::RouletteSelector(Population& _population, const Estimator& _estimator)
		: Selector(_population, _estimator), shift(0.0), sum_pop_finess(0.0)
{
	int i = -1;
	for (const auto& candidate : population)
	{
		double fitness = estimator.fitness(candidate);
		
		population_score[++i] = fitness;
		sum_pop_finess += fitness;
	}
	//no need to use kahan algorithm - on 1500 objects we have error = 0,0000000000314

	auto min_element = std::min_element(population_score.begin(), population_score.end());
	if (*min_element < 0.0) {
		shift = std::abs(*min_element) + 1.0;
		//sum_pop_finess is shifted
		sum_pop_finess += (shift * population.size());
	}
}

SolutionCandidate& RouletteSelector::Next() {
	double _sum = 0.0;
	double hit = RandomGenerator::Next()(0.0, sum_pop_finess);

	for (int i = 0; i < population.size(); ++i) {
		_sum += (population_score[i] + shift);

		if (_sum >= hit)
			return population[i];
	}

	return population.back();
}
