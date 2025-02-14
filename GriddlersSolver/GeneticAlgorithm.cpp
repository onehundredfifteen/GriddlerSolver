#include "./GeneticAlgorithm.h"
#include "./PopulationGenerator.h"
#include "./Approach/NoApproach.h"
#include "./Estimators/BasicEstimator.h"
#include "./Selectors/RouletteSelector.h"

#include "./Griddlers/ConcreteGriddler7x7.h"

void GA() {
	ConcreteGriddler7x7 myGiddler;
	NoApproach ap;
	BasicEstimator estimator(myGiddler);
	
	auto population = PopulationGenerator::Generate(20, myGiddler, ap);

	RouletteSelector selector(population, estimator);

	auto o = 2;
}

