#pragma once

#include "../types.h"

/*
Griddler Pattern base
*/

class Griddler
{
public:
	Griddler(const std::vector<BlockCollection>& _pattern_rows, const std::vector<ColumnCollection>& _pattern_cols)
		: pattern_rows(_pattern_rows), pattern_cols(_pattern_cols)
	{}

protected:
	std::vector<BlockCollection> pattern_rows;
	std::vector<ColumnCollection> pattern_cols;

public:
	const std::vector<BlockCollection>& GetRowPattern() const {
		return pattern_rows;
	}
	const std::vector<ColumnCollection>& GetColumnPattern() const {
		return pattern_cols;
	}

	const int GetImageWidth() const {
		return pattern_cols.size();
	}
	const int GetImageHeight() const {
		return pattern_rows.size();
	}
};