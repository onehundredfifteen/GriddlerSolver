#pragma once

//#include <vector>
#include <algorithm>

#include "GriddlerRow.h"


/*
ConstrainedRow

*/

class ConstrainedRow : public GriddlerRow
{
public:
	ConstrainedRow(const GriddlerRow& row) :
		GriddlerRow(row), image(getRowImage(row)) {
	}

	/*enum class CellState {
		Blank,
		Filled,
		Unknown
	};**/

private:
	const std::vector<int> image;

private:
	static std::vector<int> getRowImage(const GriddlerRow& row) {
		bool last = false;
		int block_cnt = 1;
		std::vector<int> image(row.imageWidth);

		for (unsigned c = 0; c < row.imageWidth; ++c) {
			image[c] = row.getCellByColumn(c) ? block_cnt : 0;
			if (!image[c] && last)
				++block_cnt;

			last = image[c];
		}

		return image;
	}
};