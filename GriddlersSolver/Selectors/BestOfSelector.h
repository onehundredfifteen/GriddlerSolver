#pragma once

#include <map>
#include "./Selector.h"
#include "../RandomGenerator.h"

template<int K>
class BestOfSelector : Selector
{
private:
	std::map<int, double> known_fitness;
	int element_counter;

public:
	BestOfSelector(const Population& _population, const Estimator& _estimator)
		: Selector(_population, _estimator), element_counter(0)
	{}

	virtual const SolutionCandidate& Next() override {
		int best = -1;

		for (size_t i = 0; i < K; ++i) {
			int candidate = RandomGenerator::Next()(0, population.size() - 1);

			if (best < 0 || cachedFitness(candidate) > cachedFitness(best))
				best = candidate;
		}

		return population[best];
	}

	virtual const Scores& getPopulationScore() override {
		int i = 0;
		for (const auto p : population) {
			if (known_fitness.find(i) == known_fitness.end())
				population_score[i] = estimator.candidateFitness(p);

			++i;
		}

		return population_score;
	}

private:
	double cachedFitness(int a) {
		if (known_fitness.find(a) == known_fitness.end()) {
			double fitness = estimator.candidateFitness(population[a]);
			known_fitness[a] = fitness;
			return fitness;
		}
		else return known_fitness.at(a);
	}
};
