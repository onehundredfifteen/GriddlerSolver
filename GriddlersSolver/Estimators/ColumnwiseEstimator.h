#pragma once

#include "EstimatorBase.h"

template<typename Derived>
class ColumnwiseEstimator : public EstimatorBase<Derived>
{
public:
	ColumnwiseEstimator(const Griddler& _pattern)
		: EstimatorBase<Derived>(_pattern)
	{}

	double columnFitness(const ColumnCollection& candidateColumns, const ColumnCollection& solutionProposal) const {
		return static_cast<const Derived*>(this)->columnFitness(candidateColumns, solutionProposal);
	}
	
	double columnFitness(const SolutionCandidate& candidate, int columnIndex) const {
		return static_cast<const Derived*>(this)->columnFitness(candidate.getSolvedColumnPattern(columnIndex), this->pattern.getColumnPattern()[columnIndex]);
	}
};

/*

		int t = std::count(v.begin(), v.end(), 1);


	virtual double estimateColumn(SolutionCandidate* candidate, int column) {
		std::vector<int> v, p(this->pattern[column]);

		//candidate->FillListByColumnResult(v, column);

		if(v.size() > p.size())
			std::fill_n(std::back_inserter(p), v.size() - p.size(), 0);
		else if(v.size() < p.size())
			std::fill_n(std::back_inserter(v), p.size() - v.size(), 0);
		
		return this->cosine_similarity(v, p);
		//else {
			//return std::distance(this->pattern[c].begin(), std::mismatch(this->pattern[c].begin(), this->pattern[c].end(), result[c].begin()).first)
		//}
		
	}


	/*
	double sumFitness(std::vector<int> &v, int column) {
		int sum_a = 0;
		int sum_p = 0;
		double diff, diff_fitness = 0.0;

		std::vector<int>::iterator pattern_it = pattern[column].begin();

		std::for_each(v.begin(), v.end(), [&](int n) { sum_a += n; });
		std::for_each(pattern[column].begin(), pattern[column].end(), [&](int n) { sum_p += n; });

		diff = sum_p / sum_a;
		//std::abs(sum_p - sum_a) / 
		
		for (std::vector<int>::iterator it = v.begin(); it != v.end() && _pattern_it != _pattern.end(); ++it, ++_pattern_it) {
			if (*_pattern_it != *it)
				++diff_cnt;
		}

		if (diff_cnt == 0)
			return 1.0;
		else {
			diff_fitness = ((double)diff_cnt / (double)_pattern.size());
			return 1.0 - diff_fitness;
		}

		//return std::distance(this->pattern[c].begin(), std::mismatch(this->pattern[c].begin(), this->pattern[c].end(), result[c].begin()).first)
	}


*/