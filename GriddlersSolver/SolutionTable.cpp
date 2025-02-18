// SolutionTable.cpp : Defines a solution helper
//

#include "stdafx.h"
#include <cassert>
#include "./SolutionTable.h"
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

SolutionTable::SolutionTable(const SolutionCandidate& candidate)
	: content(candidate.colCount)
{
	for (int i = 0; i < candidate.colCount; ++i) {
		// Move cells into content
		auto res = candidate.GetRowResult(i);
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

void SolutionTable::printToStream(std::ostream& stream) const {
	/*int n = 0;
	for (const auto cell : content.container) {
		stream << cellStateToChar(cell);
		if (++n % content.offset == 0)
			stream << '\n';
	}
	stream << std::flush;*/
	printToStream(stream, [](std::ostream&, int) {});
}

void SolutionTable::printToStream(std::ostream& stream, std::function<void(std::ostream&, int)> afterLineCb) const {
	int n = 0;
	for (const auto cell : content.container) {
		stream << cellStateToChar(cell);
		if (++n % content.offset == 0){
			afterLineCb(stream, n);
			stream << '\n';		
		}
	}
	stream << std::flush;
}

char SolutionTable::cellStateToChar(const CellState &cs) {
	switch (cs) {
		case CellState::Unknown: return '.';
		case CellState::Blank: return '/';
		case CellState::Filled: return '#';
		default: return '?';
	}
}