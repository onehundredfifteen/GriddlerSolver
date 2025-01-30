#pragma once

#include <vector>
#include <algorithm>

typedef std::vector<int>* ColumnCollection;
typedef std::vector<int>* BlockCollection;
typedef std::vector<int>* SpanCollection;

//#include <algorithm>

//#include "RandomGenerator.h"

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

class AbstractRow
{
public:
	/*AbstractRow(short * cells, int imgwidth ) : 
		imageWidth(imgwidth) {
	}*/

	AbstractRow(std::vector<int> &_blocks, int imgwidth) : 
		blocks(_blocks), spans(_blocks.size(), 1), imageWidth(imgwidth) {

		if(blocks.size() == 0 || (blocks.size() == 1 && blocks[0] == 0)) {
			//row is empty
			spans.push_back(imageWidth);
		}
		else {//if(getMinimalWidth() == imageWidth) {
			//row has one combination
			spans.front() = 0;
		}
	}

	AbstractRow(std::vector<int> &_blocks, std::vector<int> &_spans, int imgwidth) :
		blocks(_blocks), spans(_spans), imageWidth(imgwidth) {
	}

	AbstractRow(const AbstractRow &row) :
		blocks(row.blocks), spans(row.spans), imageWidth(row.imageWidth) {
	}

	AbstractRow(const AbstractRow &row, std::vector<int> &_spans) :
		blocks(row.blocks), spans(_spans), imageWidth(row.imageWidth) {
	}

public: //set to priv

	const std::vector<int> blocks;
	std::vector<int> spans;

	const int imageWidth;

private:
	//function to sum an array 
	int arraySum(const std::vector<int> &v) const {
		int sum = 0;
		std::for_each(v.begin(), v.end(), [&] (int n) {
			sum += n;
		});

		return sum;
	}
public:
	virtual bool operator==(const AbstractRow& other) const {
		return this->blocks == other.blocks && this->spans == other.spans;
    }

public:
	//gets minimal possible row width
	int getMinimalWidth() {
		return arraySum(blocks) + blocks.size() - 1;
	}

	//gets candidate row width
	int getWidth() {
		return arraySum(blocks) + arraySum(spans);
	}

	//gets widest possible span
	int getMaxSpanSize() {
		int s = (imageWidth - arraySum(blocks) - (blocks.size() - 1));
		if(blocks.size() > 1)
			return 1 + s;
		else if(spans.front() == imageWidth)
			return imageWidth;
		else 
			return s;
	}

	bool getCellByColumn(int col) const {
		int a = 0;
		for(unsigned k = 0 ; k < spans.size(); ++k) {
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

	std::vector<int> getRowImage() {
		bool last = false;
		int block_cnt = 1;
		std::vector<int> image(imageWidth);
		
		for(unsigned c = 0 ; c < imageWidth; ++c) {
			image[c] = this->getCellByColumn(c) ? block_cnt : 0;
			if(!image[c] && last)
				++block_cnt;

			last = image[c];
		}

		return image;
	}

	std::vector<int> getSpans() {
		return spans;
	}
};