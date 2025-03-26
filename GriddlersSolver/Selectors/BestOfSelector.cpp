#include "../stdafx.h"
#include "./BestOfSelector.h"
#include "../RandomGenerator.h"

template<int K>
BestOfSelector<K>::BestOfSelector(Population& _population, const Estimator& _estimator)
	: Selector(_population, _estimator), element_counter(0)
	{}

template<int K>
SolutionCandidate& BestOfSelector<K>::Next() {
	int best = -1;

	for (size_t i = 0; i < K; ++i) {
		int candidate = RandomGenerator::Next()(0, population.size() - 1);

		if (best < 0 || cachedFitness(candidate) > cachedFitness(best))
			best = candidate;
	}

	return population[best];
}

template<int K>
const Scores& BestOfSelector<K>::getPopulationScore() {
	int i = 0;
	for (const auto p : population) {
		if (known_fitness.find(i) == known_fitness.end())
			population_score[i] = estimator.fitness(p);

		++i;
	}

	return population_score;
}

template<int K>
double BestOfSelector<K>::cachedFitness(int a) {
	if (known_fitness.find(a) == known_fitness.end()) {
		double fitness = estimator.fitness(population[a]);
		known_fitness[a] = fitness;
		return fitness;
	}
	else return known_fitness.at(a);
}

