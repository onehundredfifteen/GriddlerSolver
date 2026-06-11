#pragma once

#include "ColumnwiseEstimator.h"

class BasicEstimator : public ColumnwiseEstimator
{
public:
	BasicEstimator(const Griddler& _pattern)
		: ColumnwiseEstimator(_pattern)
	{}

	using Estimator::candidateFitness; //for const SolutionCandidate&
	virtual double candidateFitness(const std::vector<ColumnCollection>& candidate) const override;
	virtual double columnFitness(const ColumnCollection& candidateColumns, const ColumnCollection& solution) const override;

protected:
	double longestCommonSubsequence(const ColumnCollection& solution, const ColumnCollection& target) const;
	double sizeDifference(const ColumnCollection& solution, const ColumnCollection& target) const;
	double frequenceMap(const ColumnCollection& solution, const ColumnCollection& target) const;
};