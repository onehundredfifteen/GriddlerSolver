#include <iostream>
#include <chrono>

#include "./GeneticAlgorithm.h"
#include "./PopulationGenerator.h"
#include "./Approach/NoApproach.h"
#include "./Approach/FullSolutionProvider.h"
#include "./Estimators/BasicEstimator.h"
#include "./Selectors/RouletteSelector.h"
#include "./Mutations/BasicMutation.h"
#include "./PopulationAnalyser.h"

#include "./Griddlers/ConcreteGriddler7x7.h"
#include "./Griddlers/DiagonalGriddler5x5.h"


void GA() {
	const int pop_size = 1000;
	const int max_g = 100;
	const double mut_rate = 0.05;
	const double xo_rate = 0.09;
	bool save_elites = false;

	DiagonalGriddler5x5 /*/ConcreteGriddler7x7*/ myGiddler;
	NoApproach ap;
	BasicEstimator estimator(myGiddler);
	
	Population population = PopulationGenerator::Generate(pop_size, myGiddler, ap);

	BasicMutation mutation(mut_rate);

	FullSolutionProvider fsp(myGiddler);
	SolutionCandidate solved_candidate(myGiddler, fsp);

	double last_avg = 0.0, last_med = 0.0;

	for (int generation = 1; generation < max_g; ++generation) {
		//auto start = std::chrono::high_resolution_clock::now();
		//analyse
		RouletteSelector selector(population, estimator);
		PopulationAnalyser pa(population, selector.getPopulationScore());
		

		auto solved = pa.getSolvedCandidate(myGiddler);
		if (solved) {
			std::cout << "SOLVED at generation #" << generation 
					  << " final fitness: " << estimator.fitness(solved->get()) 
				<< std::endl;
			solved->get().printToStream(std::cout);
			return;
		}
		else
		{
			std::cout << "generation #" << generation
				<< " max/min/avg/med "
				<< pa.getMax() << '/'
				<< pa.getMin() << '/'
				<< pa.getAvg() << '/'
				<< pa.getMed() << ';';

				if (generation > 1) {
					std::cout << " trend avg/med "
						<< ((pa.getAvg() > last_avg) ? 'u' : 'd') << '/'
						<< ((pa.getMed() > last_med) ? 'u' : 'd') << ';';
				}

			std::cout << std::endl;
			pa.getElite().printToStream(std::cout);
		}

		Population new_population;

		while (new_population.size() < population.size()) {
			auto candidate1 = selector.Next();
			auto candidate2 = selector.Next();

			//save elites
			if (save_elites && estimator.fitness(candidate1) >= pa.getMax()) {
				//candidate1.
				new_population.emplace_back(candidate1);
			}
			else if (save_elites &&  estimator.fitness(candidate2) >= pa.getMax())
				new_population.emplace_back(candidate2);

			candidate1.crossingOver(candidate2, xo_rate);
			candidate1.mutate(mutation);

			//if (RandomGenerator::Next()(0.0, 1.0) < xo_rate) {
			new_population.emplace_back(candidate1);
			if (new_population.size() < population.size()) {
				new_population.emplace_back(candidate2);
			}

		}
		last_avg = pa.getAvg();
		last_med = pa.getMed();
		population = std::move(new_population);
	}
}

void print(const SolutionCandidate & c) {
	//c.
}

