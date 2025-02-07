// SolutionContent.cpp : Defines a solution helper
//

#include "stdafx.h"

#include "SolutionContent.h"

CellState SolutionContent::operator()(int row, int col) const {
	int index = row * offset + col;
	return content[index];
}

void SolutionContent::PrintToStream(std::ostream& stream) const {
	int n = 0;
	for (auto cell : content) {
		stream << CellStateToChar(cell);
		if(n % offset)
			stream << '\n';
	}
	stream << std::flush;
}

char SolutionContent::CellStateToChar(const CellState &cs) {
	switch (cs) {
		case CellState::Unknown: return '.';
		case CellState::Blank: return '/';
		case CellState::Filled: return '#';
	}
}