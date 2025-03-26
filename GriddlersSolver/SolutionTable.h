#pragma once

#include <ostream>
#include <functional>
#include "./types.h"
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
private:
	Array2DWrapper<CellCollection> content;

public:
	SolutionTable(int rowCount, int colCount); // Primary constructor
	SolutionTable(const SolutionCandidate& sc);
	SolutionTable(const CellCollection& content, int offset);
	SolutionTable();

public:
	void printToStream(std::ostream& stream) const;
	void printToStream(std::ostream& stream, std::function<void(std::ostream&, int)> afterLineCb) const;

	CellState operator()(int row, int col) const;
	//bool operator()(int row, int col);
	CellCollection operator()(int row) const;

	static char SolutionTable::cellStateToChar(const CellState& cs);
	static void SolutionTable::digitMayBeNotEnough(const int c, std::ostream& stream);
};
