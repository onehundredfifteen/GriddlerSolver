#pragma once

#include "../SolutionCandidate.h"

class Estimator
{
public:
	static constexpr double LOW_FITNESS = -0.1e+015;
	static constexpr double HIGH_FITNESS = 1e+015;

protected:
	const Griddler& pattern;

public:
	Estimator(const Griddler& _pattern)
		: pattern(_pattern) 
	{}

	virtual double fitness(const SolutionCandidate& candidate) const = 0;
};