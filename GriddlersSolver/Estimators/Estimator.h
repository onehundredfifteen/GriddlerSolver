#pragma once

#include "../SolutionCandidate.h"

class Estimator
{
public:
	Estimator(const Griddler& _pattern)
		: pattern(_pattern) 
	{}

	virtual double fitness(const SolutionCandidate& candidate) const = 0;

protected:
	const Griddler& pattern;
};