#pragma once

#include "Estimator.h"

class BasicEstimator : public Estimator
{
public:
	BasicEstimator(const Griddler& _pattern);

	virtual double fitness(const SolutionCandidate& candidate) const override;

private:
	double estimate_column(const ColumnCollection& solution, const ColumnCollection& target) const;
	double estimate_column_lcs(const ColumnCollection& solution, const ColumnCollection& target) const;
};