#pragma once

#include "BasicEstimator.h"
#include <algorithm>
#include <iterator>

class ColumnwiseEstimator : public BasicEstimator
{
public:
	ColumnwiseEstimator(ColumnCollection _pattern, int _pattern_size) : BasicEstimator(_pattern, _pattern_size) {}

	virtual double MaxFitness() {
		return 2.0 *  BasicEstimator::MaxFitness();
	}

	virtual double estimate(GriddlerCandidate * candidate) {
		double fit = 0.0;
		std::vector<double> v, g(col_cnt, 1.0);

		for (int i = 0; i < col_cnt; ++i) {
			v.push_back( estimateColumn(candidate, i));
			
		}

		int t = std::count(v.begin(), v.end(), 1);
		if (t > 1)
		{

			t = t;
		}
		else t = 1;

		return t * BasicEstimator::estimate(candidate);
	}

	virtual double estimateColumn(GriddlerCandidate * candidate, int column) {
		std::vector<int> v, p(this->pattern[column]);

		candidate->FillListByColumnResult(v, column);

		if(v.size() > p.size())
			std::fill_n(std::back_inserter(p), v.size() - p.size(), 0);
		else if(v.size() < p.size())
			std::fill_n(std::back_inserter(v), p.size() - v.size(), 0);
		
		return this->cosine_similarity(v, p);
		//else {
			//return std::distance(this->pattern[c].begin(), std::mismatch(this->pattern[c].begin(), this->pattern[c].end(), result[c].begin()).first)
		//}
		
	}

	double cosine_similarity(const std::vector<int> &A, const std::vector<int> &B) const
	{
		double dot = 0.0, denom_a = 0.0, denom_b = 0.0;
		for (unsigned int i = 0u; i < A.size(); ++i) {
			dot += A[i] * B[i];
			denom_a += A[i] * A[i];
			denom_b += B[i] * B[i];
		}
		return dot / (sqrt(denom_a * denom_b));
	}

	double cosine_similarity(const std::vector<double> &A, const std::vector<double> &B) const
	{
		double dot = 0.0, denom_a = 0.0, denom_b = 0.0;
		for (unsigned int i = 0u; i < A.size(); ++i) {
			dot += A[i] * B[i];
			denom_a += A[i] * A[i];
			denom_b += B[i] * B[i];
		}
		return dot / (sqrt(denom_a * denom_b));
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
	}



	double differenceFitness(std::vector<int> &v, std::vector<int> &_pattern) {
		int diff_cnt = 0;
		double diff_fitness = 0.0;

		std::vector<int>::iterator _pattern_it = _pattern.begin();
		for (std::vector<int>::iterator it = v.begin(); it != v.end() && _pattern_it != _pattern.end(); ++it, ++_pattern_it) {
			if(*_pattern_it != *it)
				++diff_cnt;
		}

		if(diff_cnt == 0)
			return 1.0;
		else {
			diff_fitness = ((double)diff_cnt / (double)_pattern.size());
			return 1.0-diff_fitness;
		}
	}*/

};

/*
virtual double estimate( GriddlerCandidate * candidate) {
		ColumnCollection result = new std::vector<int>[col_cnt];
		int * progress = new int[col_cnt];

		for (int i = 0; i < col_cnt; ++i)
			candidate->FillListByColumnResult(result[i], i);

		for (int r = 0; i < candidate->rows[i]-> img_rows; ++r) {
			for (int c = 0; i < col_cnt; ++c) {
				if (result[c][r]) {



				}
			}
		}



		return (sizeFitness(v, pattern[column]) + differenceFitness(v, pattern[column]));
	}

	virtual double estimateColumn(GriddlerCandidate * candidate, int * progress, int column) {
		std::vector<int> v;



		//candidate->FillListByColumnResult(v, column);
		//int diff_index = std::distance(v.begin(), std::mismatch(v.begin(), v.end(), this->pattern[column].begin()).first);
		//std::vector<int>::iterator _it = this->pattern[c].size() > result[c].size() ? this->pattern[c].begin() : result[c].begin();
		//std::abs(diff_index - this->pattern[column].size())
		//if(this->pattern[c].size() >= result[c].size()) {
			//return
		//}
		//else {
			//return std::distance(this->pattern[c].begin(), std::mismatch(this->pattern[c].begin(), this->pattern[c].end(), result[c].begin()).first)
		//}

	}
*/