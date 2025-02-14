#pragma once

#include <map>
#include "./Selector.h"
#include "../RandomGenerator.h"

template<int K>
class BestOfSelector : Selector
{
public:
	BestOfSelector(Population& _population, const Estimator& _estimator)
		: Selector(_population, _estimator),
		element_counter(0)
	{}

	virtual SolutionCandidate& Next() override {
		int best = -1;

		for (size_t i = 0; i < K; ++i) {
			int candidate = RandomGenerator::Next()(0, population.size() - 1);

			if(best < 0 || cachedFitness(candidate) > cachedFitness(best))
				best = candidate;
		}
			
		return population[best];
	}

private:
	double cachedFitness(int a) {
		if (known_fitness.find(a) == known_fitness.end()) {
			double fitness = estimator.fitness(population[a]);
			known_fitness[a] = fitness;
			return fitness;
		}
		else return known_fitness.at(a);
	}


protected:
	int element_counter;
	std::map<int, double> known_fitness;
};
