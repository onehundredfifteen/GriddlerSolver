// SolutionTable.cpp : Defines a solution helper
//

#include "stdafx.h"
#include <cassert>
#include "SolutionTable.h"
#include "./SolutionCandidate.h"
#include "./Griddlers/GriddlerPreset.h"

// Primary constructor
SolutionTable::SolutionTable(int rowCount, int colCount)
	: content(colCount, rowCount * colCount, CellState::Unknown)
{}

SolutionTable::SolutionTable(const CellCollection& cells, int offset)
	: SolutionTable(cells.size() / offset, offset)
{
	content.container = cells;
}

SolutionTable::SolutionTable(const SolutionCandidate& sc)
	: SolutionTable(sc.rowCount, sc.colCount)
{
	for (int i = 0; i < sc.rowCount; ++i) {
		// Move cells into content
		auto res = sc.GetRowResult(i);
		content.container.insert(content.container.end(), 
			std::make_move_iterator(res.begin()), std::make_move_iterator(res.end()));
	}
}

SolutionTable::SolutionTable()
	: SolutionTable(0, 0)
{}

CellState SolutionTable::operator()(int row, int col) const {
	return content(row, col);
}

CellCollection SolutionTable::operator()(int row) const {
	int start = row * content.offset;
	int end = start + content.offset;
	assert(end <= content.container.size());
	return CellCollection(content.container.begin() + start, content.container.begin() + end);
}

void SolutionTable::PrintToStream(std::ostream& stream) const {
	int n = 0;
	for (auto cell : content.container) {
		stream << CellStateToChar(cell);
		if(n % content.offset)
			stream << '\n';
	}
	stream << std::flush;
}

char SolutionTable::CellStateToChar(const CellState &cs) {
	switch (cs) {
		case CellState::Unknown: return '.';
		case CellState::Blank: return '/';
		case CellState::Filled: return '#';
	}
}