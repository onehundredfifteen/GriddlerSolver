#pragma once

#include "Griddlers/Griddler.h"
#include "Rows/MutableRow.h"
#include "Approach/ApproachProvider.h"

class SolutionCandidate
{
public:
	SolutionCandidate(const Griddler &pattern, const ApproachProvider &approachProvider);
	
	ColumnCollection GetColumnCollection(int column) const;

	CellCollection GetRowResult(int row) const;
	//CellCollection GetColumnResult(int column) const;
	//std::vector<CellCollection> GetResult() const;
	/*
	void DoCrossingOver(GriddlerCandidate * partner, double chance);
	void DoMutate(double chance);

	void PrintToStream(std::ostream &stream);

	//double Fitness;*/

	bool isSolved(const Griddler& pattern) const;

public:
	const int colCount;
	const int rowCount;


private:
	std::vector<MutableRow> rows;

};