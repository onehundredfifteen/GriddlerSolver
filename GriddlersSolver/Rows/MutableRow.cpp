// MutableRow.cpp : 
//

#include "../stdafx.h"
#include "MutableRow.h"
#include "../RandomGenerator.h"

/*
MutableRow

*/

MutableRow::MutableRow(const BlockCollection& _blocks, int imgwidth, const ConstrainedRow& constraintProvider)
	: GriddlerRow(_blocks, imgwidth), final(_initFinal()) {

	if (false == final) {
		randomizeRowConstraintWise(constraintProvider);
	}
}
/*
MutableRow::MutableRow(const MutableRow& other)
	: GriddlerRow(other.blocks, other.spans, other.imageWidth), final(other.final) {

}*/

bool MutableRow::isValid() const {
	return getCurrentWidth() <= imageWidth &&
		std::find(spans.begin() + 1, spans.end(), 0) == spans.end(); //middle zeroes
}

void MutableRow::sanitize() {
	
	if (isValid()) return;

	fixMiddleZeroes();
	fixImpossibleBigSpans();
	ensureOneMaxSpanAtTime();
	trimSpansToWidth();

	assert(isValid());
}

SpanCollection& MutableRow::getSpans() {
	return this->spans;
}

void MutableRow::crossingOver(MutableRow& partner) {

	if (final || spans.size() < 2)
		return;

	int no_cross_points = RandomGenerator::Next()(1, 2);

	if (no_cross_points == 1 || spans.size() < 3) {
		int cross_point = RandomGenerator::Next()(1, spans.size() - 1);
		//xower
		std::swap_ranges(spans.begin(), spans.begin() + cross_point, partner.spans.begin());
	}
	else if(no_cross_points == 2) {
		int cross_point_begin = 0, cross_point_end = 0;

		while (cross_point_begin != cross_point_end) {
			cross_point_begin = RandomGenerator::Next()(1, spans.size() - 1);
			cross_point_end = RandomGenerator::Next()(1, spans.size() - 1);
		}

		//xower
		std::swap_ranges(spans.begin() + cross_point_begin,
			spans.begin() + cross_point_end,
			partner.spans.begin() + cross_point_begin);
	}
	else assert(false);
	
	//keep valid
	//TODO strategy?
	sanitize();
	partner.sanitize();
}

void MutableRow::mutate(const Mutation& effect) {
	if (final)
		return;
	
	//TODO rollback, leave, sanitize startegies
	effect.visit(*this);

	sanitize();
}

void MutableRow::randomizeRow() {
	const int maxQ = getMaxSpanSize(); //max possible span, only 1 possible
	const int Q = maxQ - 1; //max standard span

	//first span can be 0, last doesn't matter
	spans.front() = RandomGenerator::Next()(0, maxQ);
	bool maxSpanUsed = spans.front() == maxQ;

	//set random span for each element and we want only 1 max span 
	std::transform(spans.begin() + 1, spans.end(), spans.begin() + 1, [&Q, &maxQ, &maxSpanUsed](int span_value) {
		int new_value = (maxQ == 1) ? 1 : RandomGenerator::Next()(1, maxSpanUsed ? Q : maxQ);

		if (!maxSpanUsed && new_value == maxQ) maxSpanUsed = true;
		return new_value;
	});
}

void MutableRow::randomizeRowConstraintWise(const ConstrainedRow& constraintProvider) {
	do {
		randomizeRow();	
	} while (false == isValid() || false == constraintProvider.compareAgainst(*this));
}

bool MutableRow::_initFinal() const {
	//row is empty or one combination
	return isEmpty() || getMinimalWidth() == imageWidth;
}

void MutableRow::trimSpansToWidth() {
	while (!isValid()) {
		int unlucky = RandomGenerator::Next()(0, spans.size() - 1);
		if ((unlucky == 0 && spans[unlucky] > 0) || spans[unlucky] > 1)
			--spans[unlucky];
		else assert(false);
	}
}

void MutableRow::fixMiddleZeroes() {
	//get rid of zero-spans in the middle
	std::transform(spans.begin() + 1, spans.end(), spans.begin() + 1, [](int span_value) {
		return span_value <= 0 ? 1 : span_value;
	});
}

void MutableRow::fixImpossibleBigSpans() {
	//get rid of spans bigger than max_span
	const int max_span = this->getMaxSpanSize();
	std::transform(spans.begin(), spans.end(), spans.begin(), [&max_span](int span_value) {
		return span_value > max_span ? max_span : span_value;
	});
}
//ensure we have *up to one* span with max possible widht
void MutableRow::ensureOneMaxSpanAtTime() {
	auto test_fun = [this](int value) {
		return value == this->getMaxSpanSize();
	};
	//find max span both ways
	auto lhs = std::find_if(spans.begin(), spans.end(), test_fun);
	auto rhs_ = std::find_if(spans.rbegin(), spans.rend(), test_fun);

	if (lhs == spans.end()) return; // nothing to do
	//Convert reverse iterator to forward iterator
	auto rhs = rhs_.base() - 1;
	//do we have multiple max_spans?
	if (lhs != rhs && lhs != spans.end()) {
		//find them
		const int max_span = *lhs;
		std::vector<SpanCollection::iterator> _max_span_it;
		for (auto it = spans.begin(); it < spans.end(); ++it) {
			if (*it == max_span) {
				_max_span_it.push_back(it);
				--(*it); //we can decrement now
			}
		}
		//now pick one a random and the rest will be decremented
		int lucky = RandomGenerator::Next()(0, _max_span_it.size() - 1);
		*(_max_span_it[lucky]) = max_span;
	}
}

