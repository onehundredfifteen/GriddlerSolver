#pragma once

#include <vector>
#include <numeric>
#include <algorithm>

typedef std::vector<int> ColumnCollection;
typedef std::vector<int> BlockCollection;
typedef std::vector<int> SpanCollection;

//#include <algorithm>

//#include "RandomGenerator.h"

/*
AbstractRow

AbstractRow have collections of blocks and spans between them.

[-xx-xxx--x-]
blocks(3): 2, 3, 1
spans(4): 1, 1, 2, 1

First or last span can be 0 as the corresponding block 'sticks' to the image border, but 
the last span is virtual.
AbstractRow will have always at least 2 spans even if all row cells are filled.

[xxxxxxxxx-]
blocks(1): 9
spans(2): 0, 1

[xxxxxxxxxx]
blocks(1): 10
spans(2): 0, 0
*/

class AbstractRow
{
public:
	/*AbstractRow(int *, int imgwidth ) : 
		imageWidth(imgwidth) {
	}*/
	// Primary constructor
	AbstractRow(const BlockCollection& _blocks, const SpanCollection& _spans, int imgwidth)
		: blocks(_blocks),
		spans(_spans),
		imageWidth(imgwidth),
		blockSum(std::accumulate(blocks.begin(), blocks.end(), 0))
	{}

	// Constructor with default span initialization
	AbstractRow(const BlockCollection& _blocks, int imgwidth)
		: AbstractRow(_blocks, _initializeSpans(_blocks, imgwidth), imgwidth)
	{}

	// Copy constructor with new spans
	AbstractRow(const AbstractRow& row, const SpanCollection& _spans)
		: AbstractRow(row.blocks, _spans, row.imageWidth)
	{}

	//AbstractRow(const AbstractRow &row) :
		//blocks(row.blocks), spans(row.spans), imageWidth(row.imageWidth) {
	//}


public:
	const std::vector<int> blocks;
	const int imageWidth;

protected:
	std::vector<int> spans;
private:
	const int blockSum;

public:
	virtual bool operator==(const AbstractRow& other) const {
		return this->blocks == other.blocks && this->spans == other.spans;
    }

	const SpanCollection& getSpans() {
		return this->spans;
	}

public:
	//gets minimal possible row width
	//as sum of blocks width + minimal spaces between them
	int getMinimalWidth() const {
		return blockSum == 0 ? 0 : blockSum + blocks.size() - 1;
	}

	//gets current row width, sum of blocks & spans
	int getCurrentWidth() const {
		return blockSum + std::accumulate(spans.begin(), spans.end(), 0);
	}

	//gets widest possible span
	int getMaxSpanSize() const {
		return imageWidth - getMinimalWidth();
		/*if(blocks.size() > 1)
			return 1 + s;
		else if(spans.front() == imageWidth)
			return imageWidth;
		else 
			return s;*/
	}

	//find whether a cell at given column is full or empty
	bool getCellByColumn(int col) const {
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

private:
	static std::vector<int> _initializeSpans(const BlockCollection& _blocks, int imgwidth) {
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
};