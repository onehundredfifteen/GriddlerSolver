#pragma once

#include <ostream>
#include "GriddlerRow.h"

typedef std::vector<int>* ColumnCollection;
typedef std::vector<int>* BlockCollection;
typedef std::vector<int>* SpanCollection;

class GriddlerCandidate
{
public:
	GriddlerCandidate(BlockCollection blocks, int rows_cnt, int cols_cnt);
	GriddlerCandidate(BlockCollection blocks, SpanCollection solved_spans, int rows_cnt, int cols_cnt);
	GriddlerCandidate(const GriddlerCandidate &griddler);

	~GriddlerCandidate();

	void FillListByColumnResult(std::vector<int> &result, int column) const;
	void FillListByResult(bool * result);
	void FillListByResult(bool * result, int row_no);

	void DoCrossingOver(GriddlerCandidate * partner, double chance);
	void DoMutate(double chance);

	void PrintToStream(std::ostream &stream);

	//double Fitness;

public:
	int img_cols;
	int img_rows;

	std::vector<GriddlerRow *> rows;

private:
	void init(int r, int c);
};