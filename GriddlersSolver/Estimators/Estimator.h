#pragma once

#include "ColumnwiseEstimator.h"
#include <cmath>

class Estimator : public ColumnwiseEstimator<Estimator>
{
public:
	Estimator(const Griddler& _pattern)
		: ColumnwiseEstimator(_pattern)
	{}

	double candidateFitness(const SolutionCandidate& candidate) const {
		return ColumnwiseEstimator<Estimator>::candidateFitness(candidate);
	}

	double candidateFitness(const std::vector<ColumnCollection>& solutionProposal) const {
		double fitness = 0.0;
		auto target = pattern.getColumnPattern();

		for (int n = 0; n < solutionProposal.size(); n++)
			fitness += columnFitness(solutionProposal[n], target[n]);

		return fitness / solutionProposal.size();
	}

	double columnFitness(const ColumnCollection& candidateColumns, const ColumnCollection& solutionProposal) const {
		return cosineSimilarity(candidateColumns, solutionProposal);
	}

protected:
	double cosineSimilarity(const std::vector<int> &A, const std::vector<int> &B) const
	{
		double dot = 0.0, denom_a = 0.0, denom_b = 0.0;
		for (unsigned int i = 0u; i < A.size(); ++i) {
			dot += A[i] * B[i];
			denom_a += A[i] * A[i];
			denom_b += B[i] * B[i];
		}		
		
		if (denom_a == 0.0 || denom_b == 0.0)
			return 0.0;		
		else
			return dot / (sqrt(denom_a * denom_b));
	}
};