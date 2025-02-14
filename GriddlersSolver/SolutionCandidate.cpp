// GriddlerCandidate.cpp : Defines a new griddler entity
//

#include "stdafx.h"
#include <algorithm>

#include "./RandomGenerator.h"
#include "./Griddlers/Griddler.h"
#include "./Rows/ConstrainedRow.h"
#include "./SolutionCandidate.h"
#include "./Approach/ConstraintProvider.h"

SolutionCandidate::SolutionCandidate(const Griddler& pattern, const ConstraintProvider& approachProvider)
	: rowCount(pattern.GetImageHeight()), colCount(pattern.GetImageWidth())
{
	for (int i = 0; i < rowCount; ++i) {
		rows.emplace_back(pattern.GetRowPattern()[i], colCount, approachProvider.getRow(i));
	}
}

//gets column result //FillListByColumnResult
//looks like if we could find columns, they should be equal at some point to the pattern so griddler is resolved 
ColumnCollection SolutionCandidate::GetSolvedColumnPattern(int column) const
{
	int cnt = 0;
	ColumnCollection result;
	result.reserve(rowCount / 2);

	for (int i = 0; i < rowCount; ++i) {
		if (rows[i].getCellByColumn(column)) {
			++cnt;
		}
		else if (cnt != 0) {
			result.push_back(cnt);
			cnt = 0;
		}
	}

	if (cnt != 0)
		result.push_back(cnt);

	return std::move(result);
}

std::vector<ColumnCollection> SolutionCandidate::GetSolvedColumnPattern() const
{
	std::vector<ColumnCollection> result;
	result.reserve(colCount);

	for (int i = 0; i < colCount; ++i) {
		result.emplace_back(std::move(GetSolvedColumnPattern(i)));
	}

	return std::move(result);
}

CellCollection SolutionCandidate::GetRowResult(int row) const {
	return ConstrainedRow(rows[row]).cells;
}

bool SolutionCandidate::operator==(const SolutionCandidate& other) const {
	return this->rows == other.rows;
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
	for (const auto &cols : pattern.GetColumnPattern()) {
		if (cols != GetSolvedColumnPattern(col_idx++)) {
			return false;
		}
	}
	return true;
}


void SolutionCandidate::mutate(const Mutation& mutation) {
	auto affectedChromosomes = mutation.getAffectedChromosomes(*this);

	for (auto& chromosome : affectedChromosomes) {
		mutation.visit(chromosome);
	}
}

void SolutionCandidate::crossingOver(SolutionCandidate& partner, double chance) {
	if (*this == partner)
		return;

	chance = std::clamp(chance, 0.0, 1.0);

	for (auto it = rows.begin(), pit = partner.rows.begin(); it < rows.end(); ++it, ++pit) {
		if (RandomGenerator::Next()(0.0, 1.0) < chance) {
			(*it).crossingOver(*pit);
		}
	}
}

/*
void SolutionCandidate::PrintToStream(std::ostream& stream)
{
	for (std::vector<GriddlerRow2*>::iterator it = rows.begin(); it != rows.end(); ++it) {
		for (int col = 0; col < img_cols; ++col) {
			if ((*it)->getCellByColumn(col))
				stream << '#';
			else
				stream << ' ';

				/*

	case 0: stream << '.'; break; unkwon
				case 1: stream << '/'; break;
				case 2: stream << 'O'; break;
	
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




