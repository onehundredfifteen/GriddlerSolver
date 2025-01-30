#pragma once

//#include <vector>
#include <algorithm>

#include "AbstractRow.h"
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

First or last span can be 0 as the corresponding block 'sticks' to the image border, but 
the last span is virtual.
GriddlerRow will have always at least 2 spans even if all row cells are filled.

[xxxxxxxxx ]
blocks(1): 9
spans(2): 0, 1

[xxxxxxxxxx]
blocks(1): 10
spans(2): 0, 0
*/

class GriddlerRow : public AbstractRow
{
public:
	GriddlerRow(std::vector<int> &_blocks, int imgwidth) : 
		AbstractRow(_blocks, imgwidth), approach(nullptr) {
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
	//function generates a valid candidate
	void init() {
		if((blocks.size() == 1 && blocks[0] == 0) || (getMinimalWidth() == imageWidth)) {
			//row is empty or one combination	
			isFinal = true;
		}
		else {
			randomizeRow();
			isFinal = false;
		}
	}

	//gets effective row width
	void randomizeRow() {
		const int Q = getMaxSpanSize();
		do {
			//first span can be 0, last doesn't matter
			spans.front() = RandomGenerator::Next()(0, Q);
			//spans.back() = RandomGenerator::Next()(0, Q);

			for (std::vector<int>::iterator it = spans.begin() + 1; it < spans.end(); ++it) {
				*it = (Q == 1)? 1 : RandomGenerator::Next()(1, Q);
			}
		}
		while(by_approach() || getWidth() > imageWidth);
		/*
		if( this->getCellByColumn(1) ==false  && this->approach[1] == 2) {
				bool f,ff = getCandidateWidth() > imageWidth;
				f= by_approach();
				ff = true;
		}*/
	}

	//
	bool by_approach() {
		if(nullptr == approach)
			return false;

		for(int n = 0; n < imageWidth; ++n) {
			if(n==1)
				n=1;
			if(this->approach[n] == 0)
				continue;

			bool v = this->getCellByColumn(n);
			
			//if(n==1 && this->approach[n] == 2)
			//	n=1;
			

			if(v && this->approach[n] == 1) 
				return true;
			else if(v == false && this->approach[n] == 2 )
				return true;

			//if(v  && this->approach[n] != 2 && n == 1)
				//n=1;
		}

		return false;
	}

	void sanitize() {
		//too long, trim to width
		if(getWidth() > imageWidth) {
			std::vector<int>::iterator it = spans.end() - 1; //alvays we have at least 1 span
			//trim each span
			while(getWidth() > imageWidth) {
				if(*it > 1 || it == spans.begin())
					(*it)--;
				else
					--it;
			}
		}
	}

	void fixMiddleZeroes() {
		//get rid of zero-spans in the middle
		for (std::vector<int>::iterator it = spans.begin() + 1; it < (spans.end() - 1); ++it) {
			if(*it == 0)	
				*it = 1;
			else if(*it < 0)	
				*it = 0;
		}
	}

public:

	bool IsFinal() {
		return isFinal;
	}
	/*
	bool IsValid() {
		return getMinimalWidth() <= imageWidth;
	}*/



};