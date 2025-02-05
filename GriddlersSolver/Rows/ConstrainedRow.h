#pragma once

//#include <vector>
#include <algorithm>

#include "AbstractRow.h"


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

	/*

	case 0: stream << '.'; break; unkwon
				case 1: stream << '/'; break;
				case 2: stream << 'O'; break;
	*/

public:
	const CellCollection cells;

public:
	//produce something like this 011102033 -> [-xxx-x-xx]
	std::vector<int> getRowImage(const AbstractRow& row) const {
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
	//method won't yield unknown cells
	static CellCollection _initializeCells(const AbstractRow& row) {
		CellCollection _cells(row.imageWidth);
			
		if (row.blocks.size() == 0) {
			_cells.insert(_cells.end(), row.getSpans().front(), CellState::Blank);
		}
		else {
			auto bit = row.blocks.begin();
			for (auto sit = row.getSpans().begin(); sit < row.getSpans().end(); ++sit) {
				_cells.insert(_cells.end(), *sit, CellState::Blank);
				_cells.insert(_cells.end(), *bit, CellState::Filled);
				++bit;
			}
		}

		return std::move(_cells);
	}
};