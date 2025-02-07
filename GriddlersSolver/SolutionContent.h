#pragma once

#include <ostream>
#include "./types.h"
#include "SolutionCandidate.h"

/*
SolutionContent

can print cellcollection 
offset aware
*/

class SolutionContent
{
public:
	// Primary constructor
	SolutionContent(const SolutionCandidate& sc)
		: offset(sc.colCount)
	{		
		content.reserve(sc.rowCount * sc.colCount);
		for (int i = 0; i < sc.rowCount; ++i) {
			// Move cells into content
			auto cells = sc.GetRowResult(i);
			content.insert(content.end(), std::make_move_iterator(cells.begin()), std::make_move_iterator(cells.end()));
		}	
	}


private:
	CellCollection content;
	const int offset;
	
public:
	void PrintToStream(std::ostream& stream) const;
	CellState operator()(int row, int col) const;
	//bool operator()(int row, int col);

	static char SolutionContent::CellStateToChar(const CellState& cs);
};
