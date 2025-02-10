// ConstrainedRow.cpp : 
//

#include "../stdafx.h"
#include "ConstrainedRow.h"


/*
ConstrainedRow

*/

ConstrainedRow::ConstrainedRow()
	: GriddlerRow(dummy, 0), cells({}) {
}

ConstrainedRow::ConstrainedRow(const CellCollection& _cells)
	: GriddlerRow(dummy, 0), cells(_cells) {
}

ConstrainedRow::ConstrainedRow(const GriddlerRow& row)
	: GriddlerRow(row), cells(_initializeCells(row)) {
}

BlockCollection ConstrainedRow::dummy = {};


//produce something like this 011102033 -> [-xxx-x-xx]
std::vector<int> ConstrainedRow::getRowImage() const {
	bool last = false;
	int block_cnt = 1;
	std::vector<int> image(imageWidth);

	for (unsigned c = 0; c < imageWidth; ++c) {
		image[c] = getCellByColumn(c) ? block_cnt : 0;
		if (!image[c] && last)
			++block_cnt;

		last = image[c];
	}

	return std::move(image);
}

//compare if given row is equal to cells state
//it should have cells filled/blank at place
//returns true if equal
bool ConstrainedRow::compareAgainst(const GriddlerRow& row) const {
	if (cells.size() == 0) return true; // no constraint

	if (row.imageWidth != imageWidth) return false;

	for (int n = 0; n < imageWidth; ++n) {
		if (cells[n] == CellState::Unknown)
			continue;

		bool val = row.getCellByColumn(n);
		if ((val && cells[n] == CellState::Blank) || (!val && cells[n] == CellState::Filled)) {
			return false;
		}
	}
	return true;
}


CellCollection ConstrainedRow::_initializeCells(const GriddlerRow& row) {
	if (row.isEmpty()) {
		return CellCollection(row.imageWidth, CellState::Blank);
	}

	CellCollection _cells;
	_cells.reserve(row.imageWidth);

	auto sit = row.getSpans().begin();
	for (auto bit = row.blocks.begin(); bit < row.blocks.end(); ++bit, ++sit) {
		_cells.insert(_cells.end(), *sit, CellState::Blank);
		_cells.insert(_cells.end(), *bit, CellState::Filled);
	}
	_cells.insert(_cells.end(), row.imageWidth - row.getCurrentWidth(), CellState::Blank);

	return std::move(_cells);
}
