#pragma once

#include <ostream>
#include "./types.h"
//#include "./SolutionCandidate.h"
//#include "./Griddlers/GriddlerPreset.h"
#include "./Array2DWrapper.h"
/*
SolutionTable

can print cellcollection 
offset aware
*/

class SolutionCandidate;
class Griddler;
class GriddlerPreset;

class SolutionTable
{
public:
	// Primary constructor
	SolutionTable(int rowCount, int colCount);

	SolutionTable(const SolutionCandidate& sc);

	SolutionTable(const CellCollection& content, int offset);

	SolutionTable();

private:

	Array2DWrapper<CellCollection> content;
	
public:
	void PrintToStream(std::ostream& stream) const;
	CellState operator()(int row, int col) const;
	//bool operator()(int row, int col);
	CellCollection operator()(int row) const;

	static char SolutionTable::CellStateToChar(const CellState& cs);
};
