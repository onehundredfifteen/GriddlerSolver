#pragma once

//#include <vector>
#include <algorithm>

#include "GriddlerRow.h"


/*
ConstrainedRow

*/

class ConstrainedRow : public AbstractRow
{
public:
	ConstrainedRow() 
		: AbstractRow({0}, 0) {
	}  

	ConstrainedRow(const BlockCollection& _blocks, const CellCollection& _cells) 
		: AbstractRow(_blocks, _cells.size()), cells(_cells) {
	}

	ConstrainedRow(const AbstractRow& row)
		: AbstractRow(row), cells(_initializeCells(*this)) {
	}

	/*enum class CellState {_cells
		Blank,
		Filled,
		Unknown
	};**/
	/*

	case 0: stream << '.'; break; unkwon
				case 1: stream << '/'; break;
				case 2: stream << 'O'; break;
	*/

private:
	const CellCollection cells;

public:
	//produce something like this 011102033 -> [-xxx-x-xx]
	std::vector<int> getRowImage(const GriddlerRow& row) const {
		bool last = false;
		int block_cnt = 1;
		std::vector<int> image(row.imageWidth);

		for (unsigned c = 0; c < row.imageWidth; ++c) {
			image[c] = row.getCellByColumn(c) ? block_cnt : 0;
			if (!image[c] && last)
				++block_cnt;

			last = image[c];
		}

		return std::move(image);
	}

	//compare if given row is equal to cells state
	//it should have cells filled/blank at place
	//returns true if equal
	bool compareAgainst(const AbstractRow &row) const {
		if (this->cells.size() == 0) return true; // no constraint

		if (row.imageWidth != this->imageWidth) return false;

		for (int n = 0; n < imageWidth; ++n) {
			if (cells[n] == CellState::Unknown)
				continue;

			bool val = row.getCellByColumn(n);

			if ((val && cells[n] == CellState::Blank) || (!val && cells[n] == CellState::Filled)) {
				return true;
			}
		}
		return false;
	}

private:
	static CellCollection _initializeCells(const AbstractRow& row) {

		return CellCollection(2);
	}
};