#pragma once

#include "Selector.h"
#include "../RandomGenerator.h"

class RouletteSelector : Selector
{
public:
	RouletteSelector(Population& _population, const Estimator& _estimator)
		: Selector(_population, _estimator)
	{
		sum_pop_finess = 0.0;
		for (const auto& candidate : population)
		{
			double fitness = estimator.fitness(candidate);
			pop_finess.push_back(fitness);
			sum_pop_finess += fitness;
		}
		//no need to use kahan algorithm - on 1500 objects we have error = 0,0000000000314
	}
	
	virtual SolutionCandidate& Next() override {
		double _sum = 0.0;
		double hit = RandomGenerator::Next()(0.0, 1.0);

		for(int i = 0; i < population.size(); ++i) {
			_sum += (pop_finess[i] / sum_pop_finess);
			//norm sum
			if(_sum > hit)
				return population[i];
		}

		return population.back();
	}

protected:
	std::vector<double> pop_finess;
	double sum_pop_finess;
};