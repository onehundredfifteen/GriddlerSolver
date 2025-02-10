#include "GeneticAlgorithm.h"
#include "PopulationGenerator.h"
#include "Approach/NoApproach.h"
#include "./Griddlers/ConcreteGriddler7x7.h"

void GA() {
	ConcreteGriddler7x7 myGiddler;
	NoApproach ap;

	auto population = PopulationGenerator::Generate(2, myGiddler, ap);
	auto o = 2;
}

