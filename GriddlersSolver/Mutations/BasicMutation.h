#pragma once


#include "Mutation.h"


/*
BasicMutation

increase or decrease single span by 1

*/


class BasicMutation : public Mutation
{
public:
	virtual void visit(MutableRow& row) override {
        int mut_point = (row.getSpans().size() == 1) ? 0 : RandomGenerator::Next()(0, row.getSpans().size() - 1);
        auto& value = row.getSpans()[mut_point];

        if ((mut_point == 0 || mut_point == row.getSpans().size() - 1) && value == 0) {
            value++;
        }
        else if (mut_point >= 0 && value == 1) {
            value++;
        }
        else if (RandomGenerator::Next()(1, 100) < 48) {
            value++;
        }
        else {
            value--;
        }
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
