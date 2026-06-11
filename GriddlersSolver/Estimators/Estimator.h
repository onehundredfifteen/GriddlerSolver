#pragma once

#include "../SolutionCandidate.h"

class Estimator
{
public:
	static constexpr double LOW_FITNESS = -0.1e+015;
	static constexpr double HIGH_FITNESS = 1e+015;
	static constexpr double NOT_APPLICABLE_FITNESS = 1e+016;

protected:
	const Griddler& pattern;

public:
	Estimator(const Griddler& _pattern)
		: pattern(_pattern) 
	{}

	virtual double candidateFitness(const SolutionCandidate& candidate) const = 0;
	virtual double columnFitness(const ColumnCollection& candidateColumns, const ColumnCollection& solution) const = 0;

	virtual double columnFitness(const SolutionCandidate& candidate, int columnIndex) {
		return columnFitness(candidate.getSolvedColumnPattern(columnIndex), pattern.getColumnPattern()[columnIndex]);
	}
};