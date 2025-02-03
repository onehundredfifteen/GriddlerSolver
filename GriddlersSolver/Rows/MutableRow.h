#pragma once

//#include <vector>
#include <algorithm>

#include "GriddlerRow.h"
//#include "RandomGenerator.h"

/*
MutableRow

MutableRow can mutate

*/

typedef short Approach;

class MutableRow : private GriddlerRow
{
public:
	MutableRow(const BlockCollection& _blocks, int imgwidth) :
		GriddlerRow(_blocks, imgwidth), approach(nullptr) {
		//generate
		init();
	}

	GriddlerRow(std::vector<int> &_blocks, int imgwidth, short *_approach) :
		AbstractRow(_blocks, imgwidth), approach(_approach) {
		//generate
		init();
	}

	GriddlerRow(std::vector<int> &_blocks, std::vector<int> &_spans, int imgwidth) :
		AbstractRow(_blocks, _spans, imgwidth), isFinal(true), approach(nullptr) {
	}

	GriddlerRow(const GriddlerRow &row) :
		AbstractRow(row), isFinal(row.isFinal), approach(row.approach) {
	}
private: //set to priv

	bool isFinal;
	short *approach;

private:


	//gets effective row width
	void randomizeRow() {
		const int Q = getMaxSpanSize();
		do {
			//first span can be 0, last doesn't matter
			spans.front() = RandomGenerator::Next()(0, Q);
			//spans.back() = RandomGenerator::Next()(0, Q);

			for (std::vector<int>::iterator it = spans.begin() + 1; it < spans.end(); ++it) {
				*it = (Q == 1) ? 1 : RandomGenerator::Next()(1, Q);
			}
		} while (by_approach() || getWidth() > imageWidth);
		/*
		if( this->getCellByColumn(1) ==false  && this->approach[1] == 2) {
				bool f,ff = getCandidateWidth() > imageWidth;
				f= by_approach();
				ff = true;
		}*/
	}

	//
	bool by_approach() {
		if (nullptr == approach)
			return false;

		for (int n = 0; n < imageWidth; ++n) {
			if (n == 1)
				n = 1;
			if (this->approach[n] == 0)
				continue;

			bool v = this->getCellByColumn(n);

			//if(n==1 && this->approach[n] == 2)
			//	n=1;


			if (v && this->approach[n] == 1)
				return true;
			else if (v == false && this->approach[n] == 2)
				return true;

			//if(v  && this->approach[n] != 2 && n == 1)
				//n=1;
		}

		return false;
	}

	

public:
	void CrossingOver(GriddlerRow * partner) {

		//int cross_point = 0;

		if (spans.size() <= 1)
			return;

		//assume same size of rows bigger than 1
		int cross_point = RandomGenerator::Next()(0, spans.size() - 1);

		//xower
		std::swap_ranges(spans.begin(), spans.begin() + cross_point, partner->spans.begin());
		//keep valid
		this->sanitize();
		partner->sanitize();
	}

	//increase or decrease single span by 1
	void BasicMutation() {
		const int mut_point = (spans.size() == 1) ? 0 : RandomGenerator::Next()(0, spans.size() - 1);

		//prepare to operation
		std::vector<int>::iterator it = spans.begin() + mut_point;
		if (RandomGenerator::Next()(1, 10) > 5 && ((mut_point > 0 && *it > 1) || (mut_point == 0 && *it > 0))) //more likely to decrease
			(*it)--;
		else
			(*it)++;

		this->sanitize();
	}

	//swap random locii [spans]
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
	}

	bool IsFinal() {
		return isFinal;
	}
	/*
	bool IsValid() {
		return getMinimalWidth() <= imageWidth;
	}*/

	//gets effective row width
	void randomizeRow() {
		const int Q = getMaxSpanSize();
		do {
			//first span can be 0, last doesn't matter
			spans.front() = RandomGenerator::Next()(0, Q);
			//spans.back() = RandomGenerator::Next()(0, Q);

			for (std::vector<int>::iterator it = spans.begin() + 1; it < spans.end(); ++it) {
				*it = (Q == 1) ? 1 : RandomGenerator::Next()(1, Q);
			}
		} while (by_approach() || getWidth() > imageWidth);
		/*
		if( this->getCellByColumn(1) ==false  && this->approach[1] == 2) {
				bool f,ff = getCandidateWidth() > imageWidth;
				f= by_approach();
				ff = true;
		}*/
	}

	//
	bool by_approach() {
		if (nullptr == approach)
			return false;

		for (int n = 0; n < imageWidth; ++n) {
			if (n == 1)
				n = 1;
			if (this->approach[n] == 0)
				continue;

			bool v = this->getCellByColumn(n);

			//if(n==1 && this->approach[n] == 2)
			//	n=1;


			if (v && this->approach[n] == 1)
				return true;
			else if (v == false && this->approach[n] == 2)
				return true;

			//if(v  && this->approach[n] != 2 && n == 1)
				//n=1;
		}

		return false;
	}



};