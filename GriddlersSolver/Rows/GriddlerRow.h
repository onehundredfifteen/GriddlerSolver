#pragma once

#include <cassert>
#include <numeric>
#include <algorithm>

#include "../types.h"

/*
GriddlerRow

GriddlerRow have collections of blocks and spans between them.

[-xx-xxx--x-]
blocks(3): 2, 3, 1
spans(3): 1, 1, 2
last span is complementary

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

class GriddlerRow
{
public:
	// Primary constructor
	GriddlerRow(const BlockCollection& _blocks, const SpanCollection& _spans, int imgwidth);
		

	// Constructor with default span initialization
	GriddlerRow(const BlockCollection& _blocks, int imgwidth);

	// Copy constructor with new spans
	GriddlerRow(const GriddlerRow& row, const SpanCollection& _spans);

	//GriddlerRow(const GriddlerRow &row) :
		//blocks(row.blocks), spans(row.spans), imageWidth(row.imageWidth) {
	//}

public:
	const BlockCollection& blocks;
	const int imageWidth;

protected:
	SpanCollection spans;
private:
	const int blockSum;

public:
	virtual bool operator==(const GriddlerRow& other) const;

	const SpanCollection& getSpans() const;
	//SpanCollection getSpans(); todo version with virtual las one

public:
	//because it can be empty by two ways -> blocks {} and {0} 
	bool isEmpty() const;

	//gets minimal possible row width
	//as sum of blocks width + minimal spaces between them
	int getMinimalWidth() const;

	//gets current row width, as sum of blocks & spans /wo last span
	int getCurrentWidth() const;

	//gets widest possible span
	int getMaxSpanSize() const;

	//find whether a cell at given column is full or empty
	bool getCellByColumn(int col) const;

	unsigned int possibleCombinations() const;

	std::size_t computeHash() const;

private:
	static unsigned long long _factorial(int n);
	static unsigned long long _combinations(int n, int k);
	static SpanCollection _initializeSpans(const BlockCollection& _blocks, int imgwidth);
};