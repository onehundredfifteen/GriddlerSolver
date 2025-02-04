#pragma once

//#include <vector>
#include <algorithm>

#include "GriddlerRow.h"
#include "ConstrainedRow.h"
#include "../Mutations/Mutation.h"

/*
MutableRow

MutableRow can mutate

*/

class MutableRow : public GriddlerRow
{
public:
	MutableRow(const BlockCollection& _blocks, int imgwidth, const ConstrainedRow& constraintProvider)
		: GriddlerRow(_blocks, imgwidth) {
		if (false == this->final) {
			randomizeRowConstraintWise(constraintProvider);
		}
	}

private:


	void randomizeRow() {
		const int maxQ = getMaxSpanSize(); //max possible span, only 1 possible
		const int Q = maxQ - 1; //max standard span

		//first span can be 0, last doesn't matter
		spans.front() = RandomGenerator::Next()(0, maxQ);
		bool maxSpanUsed = spans.front() == maxQ;

		//set random span for each element and we want only 1 max span 
		std::transform(spans.begin() + 1, spans.end() - 1, spans.begin() + 1, [&Q, &maxQ, &maxSpanUsed](int span_value) {
			int new_value = (maxQ == 1) ? 1 : RandomGenerator::Next()(1, maxSpanUsed ? Q : maxQ);
			
			if (!maxSpanUsed && new_value == maxQ) maxSpanUsed = true;
			return new_value;
		});
	}

	void randomizeRowConstraintWise(const ConstrainedRow& constraintProvider) {
		do {
			randomizeRow();
			sanitize();
		} while (false == constraintProvider.compareAgainst(*this));
		/*
		if( this->getCellByColumn(1) ==false  && this->approach[1] == 2) {
				bool f,ff = getCandidateWidth() > imageWidth;
				f= by_approach();
				ff = true;
		}*/
	}

	//
	/*
	
	case 0: stream << '.'; break; unkwon
				case 1: stream << '/'; break;
				case 2: stream << 'O'; break;
	*/
	
	

public:
	SpanCollection& getSpans() {
		return this->spans;
	}

	void CrossingOver(MutableRow& partner) {

		if (spans.size() <= 2)
			return;

		//assume same size of rows bigger than 2
		int cross_point = RandomGenerator::Next()(1, spans.size() - 1);

		//xower
		std::swap_ranges(spans.begin(), spans.begin() + cross_point, partner.spans.begin());

		//keep valid
		//sanitize();
		//partner.sanitize();
	}

	

	void Mutate(Mutation &effect) {
		effect.visit(*this);

		//sanitize?
		//return isvalid?
	}



	
};