#pragma once

#include "ColumnwiseEstimator.h"

class Estimator : public ColumnwiseEstimator<Estimator>
{
public:
	Estimator(const Griddler& _pattern)
		: ColumnwiseEstimator(_pattern)
	{}

	double candidateFitness(const SolutionCandidate& candidate) const {
		return ColumnwiseEstimator<Estimator>::candidateFitness(candidate);
	}
	double candidateFitness(const std::vector<ColumnCollection>& candidate) const;
	double columnFitness(const ColumnCollection& candidateColumns, const ColumnCollection& solution) const;

protected:
	double longestCommonSubsequence(const ColumnCollection& solution, const ColumnCollection& target) const;
	double sizeDifference(const ColumnCollection& solution, const ColumnCollection& target) const;
	double frequenceMap(const ColumnCollection& solution, const ColumnCollection& target) const;
};