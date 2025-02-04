#pragma once

#include <cassert>
#include <algorithm>

#include "AbstractRow.h"
#include "../RandomGenerator.h"

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
	GriddlerRow(const BlockCollection& _blocks, int imgwidth)
		: AbstractRow(_blocks, imgwidth), final(_initFinal()) {
	}

	GriddlerRow(const BlockCollection& _blocks, const SpanCollection &_spans, int imgwidth)
		: AbstractRow(_blocks, _spans, imgwidth), final(true) {
	}

	//GriddlerRow(const GriddlerRow &row) :
		//AbstractRow(row), isFinal(row.isFinal), approach(row.approach) {
	//}
protected: 
	const bool final;

public:
	bool isLegal() const {
		return getMinimalWidth() <= imageWidth;
	}

	bool isValid() const {
		return isLegal() && getCurrentWidth() <= imageWidth;
	}

protected:
	void sanitize() {
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

private:
	bool _initFinal() const {
		//row is empty or one combination
		return (blocks.size() < 1 || (blocks.size() == 1 && blocks[0] == 0) || getMinimalWidth() == imageWidth);
	}

	void trimSpansToWidth() {
		auto _begin = spans.begin() + 1;

		for (auto it = _begin; it < spans.end(); ++it) {
			(*it)--;
			if (isValid()) return;
		}

		while (!isValid() && spans.front() > 0) {
			--spans.front();
		}
	}

	void fixMiddleZeroes() {
		//get rid of zero-spans in the middle
		std::transform(spans.begin() + 1, spans.end() - 1, spans.begin() + 1, [](int span_value) {
			return span_value <= 0 ? 1 : span_value;
		});
	}

	void adjustLastSpan() {
		//set last span value aligning to the image width
		spans.back() = imageWidth - getCurrentWidth();
	}




};