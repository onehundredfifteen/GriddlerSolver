#pragma once

#include <algorithm>

#include "GriddlerRow.h"

/*
ConstrainedRow

frozen version, can generate cellcollection and compare by cell
*/

class ConstrainedRow : public GriddlerRow
{
public:
	ConstrainedRow();

	ConstrainedRow(const CellCollection& _cells);

	ConstrainedRow(const GriddlerRow& row);

public:
	const CellCollection cells;
	 
private:
	static BlockCollection ConstrainedRow::dummy;

public:
	//produce something like this 011102033 -> [-xxx-x-xx]
	std::vector<int> getRowImage() const;

	//compare if given row is equal to cells state
	//it should have cells filled/blank at place
	//returns true if equal
	bool compareAgainst(const GriddlerRow& row) const;

private:
	//method won't yield unknown cells
	static CellCollection _initializeCells(const GriddlerRow& row);
};