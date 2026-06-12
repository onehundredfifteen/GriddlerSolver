#pragma once

#include "../SolutionCandidate.h"

template<typename Derived>
class EstimatorBase
{/*
public:
	static constexpr double LOW_FITNESS = -0.1e+015;
	static constexpr double HIGH_FITNESS = 1e+015;
	static constexpr double NOT_APPLICABLE_FITNESS = 1e+016;*/

protected:
	const Griddler& pattern;

public:
	EstimatorBase(const Griddler& _pattern)
		: pattern(_pattern)
	{}

	virtual ~EstimatorBase() = default;

	double candidateFitness(const std::vector<ColumnCollection>& solutionProposal) const {
		return static_cast<const Derived*>(this)->candidateFitness(solutionProposal);
	}

	double candidateFitness(const SolutionCandidate& candidate) const {
		return static_cast<const Derived*>(this)->candidateFitness(candidate.getSolvedColumnPattern());
	}
};