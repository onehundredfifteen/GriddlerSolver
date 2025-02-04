#pragma once

#include <ostream>
//#include "Rows/AbstractRow.h"
#include "Rows/MutableRow.h"
#include "Approach/ApproachProvider.h"

class SolutionCandidate
{
public:
	SolutionCandidate(const std::vector<BlockCollection> &block_group, const ApproachProvider &approachProvider, int row_cnt, int col_cnt);
	

	ColumnCollection GetColumnCollection(int column) const;
	CellCollection GetColumnResult(int column) const;
	std::vector<CellCollection> GetResult() const;
	/*
	void DoCrossingOver(GriddlerCandidate * partner, double chance);
	void DoMutate(double chance);

	void PrintToStream(std::ostream &stream);

	//double Fitness;*/

public:
	const int colCount;
	const int rowCount;

	std::vector<MutableRow> rows;

};