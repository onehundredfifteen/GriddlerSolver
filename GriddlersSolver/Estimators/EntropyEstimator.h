#pragma once

#include "Estimator.h"
#include <algorithm>

class EntropyEstimator : public Estimator
{
public:
	EntropyEstimator(ColumnCollection _pattern, int _pattern_size) : Estimator(_pattern, _pattern_size) {}

	virtual double estimate(GriddlerCandidate * candidate) {
		
		double fit = 0.0, q;

		return checka(candidate, this->col_cnt);
	}

private:
	virtual double MaxFitness() {
		double sum = 0;
		for (int i = 0; i < this->col_cnt; ++i) {
			sum += this->pattern[i].size();
		};
		return sum;
	}

	double checka(GriddlerCandidate * candidate, const unsigned N)
	{
		std::vector<std::vector<int>>  scan(N);
		std::vector<std::vector<int>>  rev_scan(N);
		
		double fit, fit2 = 0.0;
		std::vector<int> scanline;
		//get griddler scanlines
		for (int i = 0; i < N; ++i) {
			scanline = candidate->rows[i]->getRowImage();
			scan[i] = scanline;
			rev_scan[N - i - 1] = scanline;
		}

		fit = this->check(scan, candidate, this->col_cnt, false);
		fit2 = 0;// this->check(rev_scan, candidate, this->col_cnt, true);

		return (fit > fit2) ? fit : fit2;
	}

	double check(std::vector<std::vector<int>> &scan, GriddlerCandidate * candidate, const unsigned N, bool reverse) const
	{
		std::vector<int>::iterator it;
		std::reverse_iterator< std::vector<int>::iterator > rev;
		int last_empty, first_filled = 0;

		double fit = 0.0;
		//get griddler scanlines
		for (int c = 0; c < this->col_cnt; ++c) {
			it = this->pattern[c].begin();
			rev = this->pattern[c].rbegin();
			last_empty = -1;
			first_filled = -1;

			for (int i = 0; i < N; ++i) {
				if (scan[i][c]) { //filled

					if (last_empty == i - 1) {
						first_filled = i;
					}
					if((reverse && this->pattern[c].rend() == rev) || this->pattern[c].end() == it)
						return fit;

					if (i == N - 1) {//last cell
						int bl = i - first_filled + 1;
						if ((reverse && bl == *rev) || bl == *it) {
							fit += 1.0;
						}
						else return fit;
					}
				}
				else { //blank
					if (last_empty != i - 1 && first_filled >= 0 && first_filled < i) {
						int bl = i - first_filled;
						if ((reverse && bl == *rev) || bl == *it) {
							fit += 1.0;
						}
						else return fit;

						++rev;
						++it;
					}

					last_empty = i;
				}

				//if ((reverse && rev == this->pattern[c].rend()) || it == this->pattern[c].end())
					//break;
			}

		}

		return fit;
	}

};