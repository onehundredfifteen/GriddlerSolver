#pragma once

#include "./Selector.h"
#include "../RandomGenerator.h"

class RouletteSelector : Selector
{
public:
	RouletteSelector(Population& _population, const Estimator& _estimator)
		: Selector(_population, _estimator)
	{
		bool has_neg_fitness = false;
		sum_pop_finess = 0.0;
		for (const auto& candidate : population)
		{
			double fitness = estimator.fitness(candidate);
			if (fitness < 0.0)
				has_neg_fitness = true;

			pop_finess.push_back(fitness);
			sum_pop_finess += fitness;
		}
		//no need to use kahan algorithm - on 1500 objects we have error = 0,0000000000314
		if (has_neg_fitness)
			normalizeNegativeFitnessByShift();
		
	}
	
	virtual SolutionCandidate& Next() override {
		double _sum = 0.0;
		double hit = RandomGenerator::Next()(0.0, sum_pop_finess);

		for(int i = 0; i < population.size(); ++i) {
			_sum += pop_finess[i];
	
			if(_sum >= hit)
				return population[i];
		}

		return population.back();
	}

private:
	void normalizeNegativeFitnessByShift() {
		auto min_element = std::min_element(pop_finess.begin(), pop_finess.end());
		double shift = std::abs(*min_element) + 1.0;

		for (auto& fitness : pop_finess) {
			fitness += shift;
			sum_pop_finess += shift;
		}
	}

protected:
	std::vector<double> pop_finess;
	double sum_pop_finess;
};