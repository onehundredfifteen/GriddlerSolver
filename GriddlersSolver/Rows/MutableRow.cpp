// MutableRow.cpp : 
//

#include "../stdafx.h"
#include "MutableRow.h"


/*
MutableRow

*/

MutableRow::MutableRow(const BlockCollection& _blocks, int imgwidth, const ConstrainedRow& constraintProvider)
	: GriddlerRow(_blocks, imgwidth), final(_initFinal()) {

	if (!final) {
		randomizeRowConstraintWise(constraintProvider);
	}
}

bool MutableRow::isValid() const {
	return getCurrentWidth() <= imageWidth &&
		std::find(spans.begin() + 1, spans.end() - 1, 0) == spans.end(); //middle zeroes
}

void MutableRow::sanitize() {
	fixMiddleZeroes();

	auto _begin = spans.begin() + 1; //now we have at least 2 spans
	//only one span
	if (_begin == spans.end()) {
		adjustLastSpan();
	}

	if (isValid()) return;

	while (!isValid()) {
		trimSpansToWidth();
	}

	assert(isValid());
}

void MutableRow::randomizeRow() {
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

void MutableRow::randomizeRowConstraintWise(const ConstrainedRow& constraintProvider) {
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

bool MutableRow::_initFinal() const {
	//row is empty or one combination
	return isEmpty() || getMinimalWidth() == imageWidth;
}

void MutableRow::trimSpansToWidth() {
	auto _begin = spans.begin() + 1;

	for (auto it = _begin; it < spans.end(); ++it) {
		(*it)--;
		if (isValid()) return;
	}

	while (!isValid() && spans.front() > 0) {
		--spans.front();
	}
}

void MutableRow::fixMiddleZeroes() {
	//get rid of zero-spans in the middle
	std::transform(spans.begin() + 1, spans.end() - 1, spans.begin() + 1, [](int span_value) {
		return span_value <= 0 ? 1 : span_value;
	});
}

void MutableRow::adjustLastSpan() {
	//set last span value aligning to the image width
	spans.back() = imageWidth - getCurrentWidth();
}


SpanCollection& MutableRow::getSpans() {
	return this->spans;
}

void MutableRow::CrossingOver(MutableRow& partner) {

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



void MutableRow::Mutate(Mutation& effect) {
	effect.visit(*this);

	//sanitize?
	//return isvalid?
}
