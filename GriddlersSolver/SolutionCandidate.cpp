// GriddlerCandidate.cpp : Defines a new griddler entity
//

#include "stdafx.h"
#include <algorithm>

#include "./SolutionCandidate.h"
#include "./RandomGenerator.h"
#include "./Griddlers/Griddler.h"
#include "./Rows/ConstrainedRow.h"
#include "./Approach/ConstraintProvider.h"

SolutionCandidate::SolutionCandidate(const Griddler& _pattern, const ConstraintProvider& _approachProvider)
	: pattern(_pattern), rowCount(_pattern.GetImageHeight()), colCount(_pattern.GetImageWidth())
{
	for (int i = 0; i < rowCount; ++i) {
		rows.emplace_back(pattern.getRowPattern()[i], colCount, _approachProvider.getRow(i));
	}
}
/*
SolutionCandidate::SolutionCandidate(const SolutionCandidate& other)
	: colCount(other.colCount), rowCount(other.rowCount)
{
	rows.reserve(other.rowCount);
	for (auto r : other.rows) {
		rows.emplace_back();
	}
}*/
/*
SolutionCandidate& SolutionCandidate::operator=(const SolutionCandidate& other)
{
	if (this == &other) {
		return *this;
	}
	const_cast<int&>(this->colCount) = other.colCount;
	const_cast<int&>(this->rowCount) = other.rowCount;
	this->rows = other.rows;

	return *this;
}*/

//gets column result //FillListByColumnResult
//looks like if we could find columns, they should be equal at some point to the pattern so griddler is resolved 
ColumnCollection SolutionCandidate::getSolvedColumnPattern(int column) const
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

std::vector<ColumnCollection> SolutionCandidate::getSolvedColumnPattern() const
{
	std::vector<ColumnCollection> result;
	result.reserve(colCount);

	for (int i = 0; i < colCount; ++i) {
		result.emplace_back(std::move(getSolvedColumnPattern(i)));
	}

	return std::move(result);
}

CellCollection SolutionCandidate::getRowAsCells(int row) const {
	return ConstrainedRow(rows[row]).cells;
}

const Griddler& SolutionCandidate::getPattern() const {
	return pattern;
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

bool SolutionCandidate::isSolved() const {
	int col_idx = 0;
	for (const auto &cols : pattern.getColumnPattern()) {
		auto d = getSolvedColumnPattern(col_idx++);
		if (cols != d) {
			return false;
		}
	}
	return true;
	/*const auto& columnPattern = pattern.getColumnPattern();
	return std::equal(columnPattern.begin(), columnPattern.end(),
		[this](const auto& col, int index) {
		return col == getSolvedColumnPattern(index);
	});*/
}

bool SolutionCandidate::isLethal() const {
	return std::find_if(rows.begin(), rows.end(), [](const auto& row){
		return row.isValid() == false;
	}) != rows.end();
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

void SolutionCandidate::printToStream(std::ostream& stream) const
{
	SolutionTable image(*this);
	
	std::vector<ColumnCollection> scp = getSolvedColumnPattern();
	auto longestColumns = std::max_element(scp.begin(), scp.end(),
		[](const auto& a, const auto& b) {
		return a.size() < b.size();
	});

	for (int line = 0; line < longestColumns->size(); ++line) {
		for (int i = 0; i < colCount; ++i) {
			if (line < scp[i].size()) {
				SolutionTable::digitMayBeNotEnough(scp[i][line], stream);
			}
			else
				stream << ' ';
		}
		stream << '\n';
	}
	
 	image.printToStream(stream, [this](std::ostream& s, int idx) {
		const int row_no = (idx / this->rowCount) - 1;
		const auto& blocks = this->getPattern().getRowPattern();
		s << "->";
		for (const auto& b : blocks[row_no]) {
			SolutionTable::digitMayBeNotEnough(b, s);
			s << ' ';
		}
	});

	stream << std::endl;
}




