#pragma once

#include "../SolutionCandidate.h"

class Estimator
{
public:
	Estimator(ColumnCollection _pattern, int _pattern_size) 
		: pattern(_pattern), col_cnt(_pattern_size) {
	}
	virtual ~Estimator() {}

	virtual double operator()(SolutionCandidate* candidate) {
		return this->estimate(candidate) / this->MaxFitness();
	}

	virtual double MaxFitness() = 0;


protected:
	ColumnCollection pattern;
	const int col_cnt;

protected:
	virtual double estimate(SolutionCandidate* _candidate) = 0;
};