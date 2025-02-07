#pragma once

#include "Estimator.h"

class BasicEstimator : public Estimator
{
public:
	BasicEstimator(ColumnCollection _pattern, int _pattern_size) : Estimator(_pattern, _pattern_size) {}
	
	virtual double MaxFitness() {
		return this->col_cnt;
	}

	virtual double estimate(SolutionCandidate* candidate) {
		double fit = 0.0;
		for(int i = 0; i < col_cnt; ++i) {
			fit += estimateColumn(candidate, i);
		}

		return fit;
	};

	virtual double estimateColumn(SolutionCandidate* candidate, int column) {
		/*std::vector<int> v;

		candidate->FillListByColumnResult(v, column);
		
		if(v.size() != pattern[column].size()) {
			//double size_diff = std::abs((int)(v.size() - pattern[column].size()));
			return 0.0;// * (1 / size_diff);
		}
		else if(std::equal(v.begin(), v.end(), pattern[column].begin()))
			return 1.0;
		else {
			//return 0.315;
			int diff_cnt = 0;
			double val_diff_fitness = 0.0;

			std::vector<int>::iterator pattern_it = pattern[column].begin();
			for (std::vector<int>::iterator it = v.begin(); it < v.end(); ++it, ++pattern_it) {
				if(*pattern_it != *it) {
					val_diff_fitness += (1.0 / std::abs(*pattern_it - *it));
					++diff_cnt;
				}
			}

			if(diff_cnt == pattern[column].size())
				return 0.0;

			
			return 0.25 *(val_diff_fitness / diff_cnt);
		}*/
	}

	virtual void FillListByFitting(std::vector<double> &fit, SolutionCandidate* candidate) {
		fit.push_back(this->estimate(candidate));
		for (int i = 0; i < col_cnt; ++i) {
			fit.push_back(estimateColumn(candidate, i));
		}
	}
};