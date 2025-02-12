#pragma once

#include "../SolutionCandidate.h"

class Estimator
{
public:
	Estimator(const Griddler& _pattern)
		: pattern(_pattern) 
	{}

	//double operator()(const SolutionCandidate& candidate) {
		//return this->estimate(candidate);// / this->MaxFitness();
	//}

	virtual double fitness(const SolutionCandidate& candidate) const = 0;

	//virtual double MaxFitness() = 0;

protected:
	const Griddler& pattern;

//protected:
	////virtual double estimate(const SolutionCandidate &candidate) = 0;
};