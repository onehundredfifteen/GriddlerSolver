// GriddlerCandidate.cpp : Defines a new griddler entity
//

#include "stdafx.h"
#include <algorithm>

#include "Griddlers/Griddler.h"
#include "Rows/ConstrainedRow.h"
#include "SolutionCandidate.h"

SolutionCandidate::SolutionCandidate(const Griddler& pattern, const ApproachProvider& approachProvider)
	: rowCount(pattern.GetRowPattern().size()), colCount(pattern.GetColumnPattern().size())
{

	for (int i = 0; i < rowCount; ++i) {
		rows.emplace_back(pattern.GetRowPattern()[i], colCount, approachProvider.getRow(i));
	}
}

//gets column result //FillListByColumnResult
//looks like if we could find columns, they should be equal at some point to the pattern so griddler is resolved 
ColumnCollection SolutionCandidate::GetColumnCollection(int column) const
{
	int cnt = 0;
	ColumnCollection result(rowCount / 2);

	for (int i = 0; i < rowCount; ++i) {
		if (rows[i].getCellByColumn(column)) {
			++cnt;
		}
		else if (cnt != 0) {
			result.push_back(cnt);
			cnt = 0;
		}
	}

	if (cnt != 0) //if there is no span at the border
		result.push_back(cnt);

	return std::move(result);
}

CellCollection SolutionCandidate::GetRowResult(int row) const {
	return ConstrainedRow(rows[row]).cells;
}

//FillListByResult
/*
void SolutionCandidate::GetColumnResult(int column)
{
	for(int r = 0; r < img_rows; ++r) {
		for(int i = 0; i < img_cols; ++i) {
			result[img_cols * r + i] = rows[r]->getCellByColumn(i);
		}
	}
}
CellCollection SolutionCandidate::GetColumnResult(int column) const
{
	CellCollection result();
	for(int i = 0; i < img_cols; ++i) {
		result[i] = rows[row_no]->getCellByColumn(i);
	}
}*/

bool SolutionCandidate::isSolved(const Griddler& pattern) const {
	int col_idx = 0;
	for (auto cols : pattern.GetColumnPattern()) {
		if (cols != GetColumnCollection(col_idx++)) {
			return false;
		}
	}

	return true;
}
/**
//Xover
void GriddlerCandidate::DoCrossingOver(GriddlerCandidate* partner, double chance)
{
	if (this == partner || RandomGenerator::Next()(0.0, 1.0) < chance)
		return;
*/
	/*if(RandomGenerator::Next()(0.0, 1.0) >= chance) {
		int chromosome = -1;

		while(chromosome < 0 || rows[chromosome]->IsFinal()) {
			chromosome = RandomGenerator::Next()(0, rows.size() - 1);
		}

		rows[chromosome]->CrossingOver(partner->rows[chromosome]);
	}*/
/*

	int i = 0;
	for (std::vector<GriddlerRow*>::iterator it = rows.begin(); it != rows.end(); ++it, ++i) {
		if (false == (*it)->IsFinal()) {
			(*it)->CrossingOver(partner->rows[i]);
		}
	}
}
//Operator mutation
void GriddlerCandidate::DoMutate(double chance)
{
	if (RandomGenerator::Next()(0.0, 1.0) > chance) {
		int chromosome = -1;

		while (chromosome < 0 || rows[chromosome]->IsFinal()) {
			chromosome = RandomGenerator::Next()(0, rows.size() - 1);
		}

		if (rows[chromosome]->spans.size() > 2 && RandomGenerator::Next()(0.0, 1.0) > 0.5)
			rows[chromosome]->SwapMutation();
		else
			rows[chromosome]->BasicMutation();
	}


	/*for (std::vector<GriddlerRow*>::iterator it = rows.begin(); it != rows.end(); ++it, ++i) {
		if(false == (*it)->IsFinal() && RandomGenerator::Next()(0.0, 1.0) >= chance) {
			int f = RandomGenerator::Next()(1, 20);
			if(f <= 3) {
				(*it)->BasicMutation();
			}
			//else if(f == 4)
				//(*it)->BasicMutation();
			//else if(f == 5)// || f==5)
				//(*it)->BasicMutation();
		}
	}
	int i = 0;
	for (std::vector<GriddlerRow*>::iterator it = rows.begin(); it != rows.end(); ++it, ++i) {
		if(false == (*it)->IsFinal() && RandomGenerator::Next()(0.0, 1.0) >= chance) {
			int f = RandomGenerator::Next()(1, 20);
			if(f <= 3) {
				(*it)->BasicMutation();
			}
			//else if(f == 4)
				//(*it)->BasicMutation();
			//else if(f == 5)// || f==5)
				//(*it)->BasicMutation();
		}
	}*/
//}
/*
void GriddlerCandidate::PrintToStream(std::ostream& stream)
{
	for (std::vector<GriddlerRow*>::iterator it = rows.begin(); it != rows.end(); ++it) {
		for (int col = 0; col < img_cols; ++col) {
			if ((*it)->getCellByColumn(col))
				stream << '#';
			else
				stream << ' ';
		}

		stream << "...";
		for (int i = 0; i < (*it)->spans.size(); ++i) {
			stream << (*it)->spans[i] << ' ';
		}

		stream << "\tblc:";
		for (int i = 0; i < (*it)->blocks.size(); ++i) {
			stream << (*it)->blocks[i] << ' ';
		}

		stream << '\n';
	}
	stream << std::endl;

	int max_line = 0;
	std::vector< std::vector<int>> c;
	for (int col = 0; col < img_cols; ++col) {
		std::vector<int> v;
		FillListByColumnResult(v, col);
		c.push_back(v);

		if (max_line < v.size())
			max_line = v.size();
	}

	for (int line = 0; line < max_line; ++line) {
		for (int i = 0; i < img_cols; ++i) {
			if (line < c[i].size()) {
				if (c[i][line] > 9) {
					char r = 'A';
					r += (c[i][line] - 10);
					stream << r;
				}
				else
					stream << c[i][line];
			}
			else
				stream << ' ';

		}
		stream << '\n';
	}

	stream << std::endl;
}*/




