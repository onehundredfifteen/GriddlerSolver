#pragma once

#include <vector>
#include <algorithm>

#include "RandomGenerator.h"

/*
GriddlerRow

GriddlerRow have collections of blocks and spans between them.

[ xx xxx  x ]
blocks(3): 2, 3, 1
spans(4): 1, 1, 2, 1

GriddlerRow acts as a chromosome where only spans are rendomized
so they can affect candidate.
GriddlerRow will deliver only a valid combination, even if mutated.

First or last span can be 0 as the corresponding block 'sticks' to the image border.
GriddlerRow will have always at least 2 spans even if all row cells are filled.

[xxxxxxxxx ]
blocks(1): 9
spans(2): 0, 1

[xxxxxxxxxx]
blocks(1): 10
spans(2): 0, 0
*/

class GriddlerRow
{
public:
	GriddlerRow(std::vector<int> &_blocks, int imgwidth) : 
		blocks(_blocks), spans(_blocks.size() + 1), imageWidth(imgwidth) {
		//generate
		init();
	}

	GriddlerRow(std::vector<int> &_blocks, std::vector<int> &_spans, int imgwidth) :
		blocks(_blocks), spans(_spans), imageWidth(imgwidth), isFinal(true) {
	}

	GriddlerRow(const GriddlerRow &row) :
		blocks(row.blocks), spans(row.spans), imageWidth(row.imageWidth), isFinal(row.isFinal) {
	}
public: //set to priv

	std::vector<int> blocks;
	std::vector<int> spans;

	bool isFinal;
	const int imageWidth;

private:

	//function to sum an array 
	int arraySum(std::vector<int> &v) {
		int sum = 0;
		std::for_each(v.begin(), v.end(), [&] (int n) {
			sum += n;
		});

		return sum;
	}

	//gets minimal possible row width
	int getMinimalWidth() {
		return arraySum(blocks) + blocks.size() - 1;
	}

	//gets candidate row width
	int getCandidateWidth() {
		return arraySum(blocks) + arraySum(spans);
	}

	//gets real row width excluding last 'virtual' span
	int getCandidateEffectiveWidth() {
		return getCandidateWidth() - spans.back(); //tweak
	}

	//gets effective row width
	void randomizeRow() {
		const int Q = imageWidth - arraySum(blocks) - (blocks.size()-1);

		do {
			//first and last span can be 0
			spans.front() = RandomGenerator::Next()(0, Q);
			spans.back() = RandomGenerator::Next()(0, Q);

			for (std::vector<int>::iterator it = spans.begin() + 1; it < (spans.end() - 1); ++it) {
				*it = RandomGenerator::Next()(1, Q);
			}
		}
		while(getCandidateWidth() != /*!= >*/ imageWidth);
	}
	
	//function generates a valid candidate
	void init() {
		if(spans.size() == 1) {
			//row is empty
			spans.front() = imageWidth;
			isFinal = true;
		}
		else if(getMinimalWidth() == imageWidth) {
			//row has one combination
			spans.front() = spans.back() = 0;
			for (std::vector<int>::iterator it = spans.begin() + 1; it < (spans.end() - 1); ++it) {
				*it = 1;
			}
			isFinal = true;
		}
		else {
			randomizeRow();
			isFinal = false;
		}
	}

	void sanitize() {
		//too long, trim to width
		if(getCandidateWidth() > imageWidth) {
			std::vector<int>::iterator it = spans.end() - 2; //alvays we have at least 2 spans
			spans.back() = 0;

			if(getCandidateWidth() > imageWidth) {
			}

			//trim each span
			while(getCandidateEffectiveWidth() > imageWidth) {
				if(*it > 1 || it == spans.begin())
					(*it)--;
				else
					--it;
			}
		}
	}

	void checkForMiddleZeroes() {
		//get rid of zero-spans in the middle
		for (std::vector<int>::iterator it = spans.begin() + 1; it < (spans.end() - 1); ++it) {
			if(*it == 0)	
				*it = 1;
		}
	}

public:
	bool GetCellByColumn(int col) {
		int a = 0;
		for(unsigned int k = 0 ; k < spans.size(); ++k) {
			for(int n = 0 ; n < spans[k]; ++n) {
				if(a++ == col)
					return false;
			}

			if(k < blocks.size()) {
				for(int n = 0 ; n < blocks[k]; ++n) {
					if(a++ == col)
						return true;
				}
			}
		}
		return false;
	}

	void CrossingOver(GriddlerRow * partner) {
		//assume same size of rows bigger than 1
		int cross_point = RandomGenerator::Next()(1, spans.size() - 1);

		//xower
		std::swap_ranges(spans.begin(), spans.begin() + cross_point, partner->spans.begin());
		//keep valid
		this->sanitize();
		partner->sanitize();
	}

	//increase or decrease single span
	void BasicMutation() {
		//assume size of row bigger than 1
		const int mut_point = RandomGenerator::Next()(0, spans.size() - 1);

		//prepare to operation
		std::vector<int>::iterator it = spans.begin() + mut_point;
		if(RandomGenerator::Next()(1, 10) > 5 && *it > 1) //more likely to decrease
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
		}
		while(swap_point1 == swap_point2);

		//prepare to operation
		a = spans.begin() + swap_point1;
		b = spans.begin() + swap_point2;
		std::iter_swap(a, b);

		this->checkForMiddleZeroes();
		this->sanitize();
	}

	//reverse
	void ReverseMutation() {
		if(spans.size() < 4) {
			std::reverse(spans.begin(), spans.end());
		}
		else {
			std::vector<int>::iterator a, b;
			int rev_point1, rev_point2 = RandomGenerator::Next()(0, spans.size() - 1);

			//get both random and different points
			do {
				rev_point1 = RandomGenerator::Next()(0, spans.size() - 1);
			}
			while(rev_point1 == rev_point2);

			//prepare to operation
			//a = spans.begin() + std::min(rev_point1, rev_point2);
			//b = spans.begin() + std::max(rev_point1, rev_point2);
			std::reverse(a, b);
		}
		
		this->checkForMiddleZeroes();
		this->sanitize();
	}

	void NewMutation() {
		//assume size of row bigger than 1
		const int mut_point = RandomGenerator::Next()(0, spans.size() - 1);
		const int Q = imageWidth - arraySum(blocks) - (blocks.size() - 1);

		
		//prepare to operation
		std::vector<int>::iterator it = spans.begin() + mut_point;
		int low = (it == spans.begin() || it == spans.end()) ? 0 : 1;

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



};