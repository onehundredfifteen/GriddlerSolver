#pragma once

#include "../GriddlerCandidate.h"

class Estimator
{
public:
	Estimator(ColumnCollection _pattern, int _pattern_size) 
		: pattern(_pattern), col_cnt(_pattern_size) {
	}
	virtual ~Estimator() {}

	virtual double operator()(GriddlerCandidate * candidate) {
		return this->estimate(candidate) / this->MaxFitness();
	}

	virtual double MaxFitness() = 0;


protected:
	ColumnCollection pattern;
	const int col_cnt;

protected:
	virtual double estimate(GriddlerCandidate * _candidate) = 0;
};