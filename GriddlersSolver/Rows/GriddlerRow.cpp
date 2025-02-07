// GriddlerRow.cpp : 
//

#include "../stdafx.h"
#include "GriddlerRow.h"


/*
GriddlerRow

GriddlerRow have collections of blocks and spans between them.

[-xx-xxx--x-]
blocks(3): 2, 3, 1
spans(4): 1, 1, 2, 1

First or last span can be 0 as the corresponding block 'sticks' to the image border, but
the last span is virtual.
GriddlerRow will have always at least 2 spans even if all row cells are filled.

[xxxxxxxxx-]
blocks(1): 9
spans(2): 0, 1

[xxxxxxxxxx]
blocks(1): 10
spans(2): 0, 0
*/

GriddlerRow::GriddlerRow(const BlockCollection& _blocks, const SpanCollection& _spans, int imgwidth)
	: blocks(_blocks),
	spans(_spans),
	imageWidth(imgwidth),
	blockSum(std::accumulate(blocks.begin(), blocks.end(), 0)) {
		assert(getMinimalWidth() <= imageWidth);
}

	// Constructor with default span initialization
GriddlerRow::GriddlerRow(const BlockCollection& _blocks, int imgwidth)
	: GriddlerRow(_blocks, _initializeSpans(_blocks, imgwidth), imgwidth)
{}

	// Copy constructor with new spans
GriddlerRow::GriddlerRow(const GriddlerRow& row, const SpanCollection& _spans)
	: GriddlerRow(row.blocks, _spans, row.imageWidth)
{}

bool GriddlerRow::operator==(const GriddlerRow& other) const {
	return this->blocks == other.blocks && this->spans == other.spans;
}

const SpanCollection& GriddlerRow::getSpans() const {
	return this->spans;
}

//because it can be empty by two ways -> blocks {} and {0} 
bool GriddlerRow::isEmpty() const {
	return blocks.size() == 0 || (blocks.size() == 1 && blocks[0] == 0);
}

//gets minimal possible row width
//as sum of blocks width + minimal spaces between them
int GriddlerRow::getMinimalWidth() const {
	return blockSum == 0 ? 0 : blockSum + blocks.size() - 1;
}

//gets current row width, as sum of blocks & spans /wo last span
int GriddlerRow::getCurrentWidth() const {
	return blockSum + std::accumulate(spans.begin(), spans.end() - 1, 0);
}

//gets widest possible span
int GriddlerRow::getMaxSpanSize() const {
	return imageWidth - getMinimalWidth();
}

//find whether a cell at given column is full or empty
bool GriddlerRow::getCellByColumn(int col) const {
	int acc = 0;
	for (unsigned k = 0; k < spans.size(); ++k) {
		acc += spans[k];
		if (acc > col) return false;

		if (k < blocks.size()) {
			acc += blocks[k];
			if (acc > col) return true;
		}
	}
	return false;
}

unsigned int GriddlerRow::possibleCombinations() const {
	if (isEmpty()) {
		return 1;
	}

	const int k = blocks.size();
	const int total_len = (k - 1) + blockSum;
	int free_space = imageWidth - total_len;
	return _combinations(free_space + k, k);
	/*
	if (blocks.size() == 1 && blocks[0] == 0) {
		return 1;
	}
	return combinations(this->getMinimalWidth() + blocks.size(), blocks.size());*/
}

std::size_t GriddlerRow::computeHash() const {
	std::size_t seed = 0;
	std::hash<int> hasher;
	for (const int& element : spans) {
		seed ^= hasher(element) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	return seed;
}

unsigned long long GriddlerRow::_factorial(int n) {
	unsigned long long result = 1;
	for (int i = 1; i <= n; ++i) {
		result *= i;
	}
	return result;
}

unsigned long long GriddlerRow::_combinations(int n, int k) {
	if (k > n) return 0;
	return _factorial(n) / (_factorial(k) * _factorial(n - k));
}

SpanCollection GriddlerRow::_initializeSpans(const BlockCollection& _blocks, int imgwidth) {
	//empty row
	if (_blocks.size() == 0 || (_blocks.size() == 1 && _blocks[0] == 0)) {
		return { imgwidth };
	}
	//full row
	else if (_blocks.size() == 1 && _blocks[0] == imgwidth) {
		return { 0, 0 };
	}

	std::vector<int> spans(_blocks.size() + 1, 1);
	spans.front() = 0;
	return std::move(spans);
}
