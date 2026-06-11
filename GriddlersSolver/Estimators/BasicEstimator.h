#pragma once

#include "Estimator.h"

class BasicEstimator : public Estimator
{
public:
	BasicEstimator(const Griddler& _pattern);
	virtual double candidateFitness(const SolutionCandidate& candidate) const override;
	virtual double columnFitness(const ColumnCollection& solution, const ColumnCollection& target) const;

private:
	double estimate_column_countmap(const ColumnCollection& solution, const ColumnCollection& target) const;
	double estimate_column_lcs(const ColumnCollection& solution, const ColumnCollection& target) const;
};