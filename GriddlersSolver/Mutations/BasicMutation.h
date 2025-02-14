#pragma once

#include "./Mutation.h"
#include "../Rows/MutableRow.h"

/*
BasicMutation

increase or decrease single span by 1
can be harmful
*/


class BasicMutation : public Mutation
{
public:
	BasicMutation(double _mutation_rate)
		: Mutation(_mutation_rate)
	{}

	void visit(MutableRow& row) const override {
		for (auto& span : row.getSpans()) {
			if (RandomGenerator::Next()(0.0, 1.0) < mutation_rate) {
				mutateRow(span);
			}
		}
	}

protected:
	void mutateRow(int& span) const {
		if (RandomGenerator::Next()(0.0, 1.0) < 0.5)
			--span;
		else ++span;
	}

	//mutate only one chromosome
	virtual Chromosomes getAffectedChromosomes(SolutionCandidate& candidate) const {
		int affected = RandomGenerator::Next()(0, candidate.rowCount - 1);
		return { getMutableRows(candidate)[affected] };
	}

    /*//swap random locii [spans]
	void SwapMutation() {
		//assume size of row bigger than 1
		std::vector<int>::iterator a, b;
		int swap_point1, swap_point2 = RandomGenerator::Next()(0, spans.size() - 1);

		//get both random and different points
		do {
			swap_point1 = RandomGenerator::Next()(0, spans.size() - 1);
		} while (swap_point1 == swap_point2);

		//prepare to operation
		a = spans.begin() + swap_point1;
		b = spans.begin() + swap_point2;
		std::iter_swap(a, b);

		this->fixMiddleZeroes();
		this->sanitize();
	}

	//reverse
	void ReverseMutation() {
		if (spans.size() < 3) {
			std::reverse(spans.begin(), spans.end());
		}
		else {
			std::vector<int>::iterator a, b;
			int rev_point1, rev_point2 = RandomGenerator::Next()(0, spans.size() - 1);

			//get both random and different points
			do {
				rev_point1 = RandomGenerator::Next()(0, spans.size() - 1);
			} while (rev_point1 == rev_point2);

			//prepare to operation
			//a = spans.begin() + std::min(rev_point1, rev_point2);
			//b = spans.begin() + std::max(rev_point1, rev_point2);
			std::reverse(a, b);
		}

		this->fixMiddleZeroes();
		this->sanitize();
	}

	void NewMutation() {
		//assume size of row bigger than 1
		const int mut_point = (spans.size() == 1) ? 0 : RandomGenerator::Next()(0, spans.size() - 1);
		const int Q = getMaxSpanSize();

		//prepare to operation
		std::vector<int>::iterator it = spans.begin() + mut_point;
		int low = (it == spans.begin()) ? 0 : 1;

		*it = RandomGenerator::Next()(low, Q);

		this->sanitize();
	}*/
};
