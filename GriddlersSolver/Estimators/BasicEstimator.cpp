#include "../stdafx.h"
#include <map>
#include "BasicEstimator.h"

BasicEstimator::BasicEstimator(const Griddler& _pattern)
	: Estimator(_pattern)
{}

double BasicEstimator::fitness(const SolutionCandidate& candidate) const {
	double fitness = 0.0, global_score = 0.0;
	auto solution = candidate.getSolvedColumnPattern();
	auto target = pattern.getColumnPattern();

	//sum col fitness
	for (int n = 0; n < solution.size(); ++n)
		fitness += estimate_column(solution[n], target[n]);

	//find longest column
	size_t max_col_size = 0;
	for (const auto& e : solution) max_col_size = std::max(max_col_size, e.size());
	for (const auto& e : target) max_col_size = std::max(max_col_size, e.size());

	//global fitness
	for (size_t c = 0; c < max_col_size; ++c) {
		int sum_solution = 0, sum_target = 0;
		for (size_t r = 0; r < solution.size(); ++r) {

			if (c < solution[r].size())
				sum_solution += solution[r][c];

			if (c < target[r].size())
				sum_target += target[r][c];
		}
		global_score -= std::abs(sum_solution - sum_target);
	}

	return fitness + global_score;
};

double BasicEstimator::estimate_column(const ColumnCollection& solution, const ColumnCollection& target) const {

	double a = estimate_column_countmap(solution, target);
	double b = estimate_column_lcs(solution, target);

		
	return estimate_column_countmap(solution, target) + 
		   estimate_column_lcs(solution, target);
}

double BasicEstimator::estimate_column_countmap(const ColumnCollection& solution, const ColumnCollection& target) const {
	std::map<int, int> freq_solution, freq_target;

	//1. Count elements fitness
	for (int len : solution) ++freq_solution[len];
	for (int len : target) ++freq_target[len];

	double count_score = 0.0;
	for (const auto& [length, count] : freq_target) {
		count_score -= std::abs(freq_solution[length] - count);
	}

	return count_score / target.size();
}

double BasicEstimator::estimate_column_lcs(const ColumnCollection& solution, const ColumnCollection& target) const {
	//longest common subsequence
	int n = solution.size();
	int t = target.size();
	/*
	std::vector<std::vector<int>> dp(n + 1, std::vector(t + 1, 0));

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= t; ++j) {
			if (solution[i - 1] == target[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else {
				dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}*/
	Array2DWrapper<std::vector<int>> lcs(t + 1, (t + 1) * (n + 1), 0);

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= t; ++j) {
			if (solution[i - 1] == target[j - 1]) {
				lcs(i, j) = lcs(i - 1, j - 1) + 1;
			}
			else {
				lcs(i, j) = std::max(lcs(i - 1, j), lcs(i, j - 1));
			}
		}
	}
	//double order_score2 = lcs(n, t);
	//double order_score3 = dp[n][t];

	//1.0 - full match
	//0.0 - no common elements & order
	double lcd = lcs(n, t);
	return lcs(n, t) / target.size();
}