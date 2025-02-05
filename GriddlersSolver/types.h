#pragma once

#include <vector>

enum class CellState {
	Blank,
	Filled,
	Unknown
};

typedef std::vector<int> ColumnCollection;
typedef std::vector<int> BlockCollection;
typedef std::vector<int> SpanCollection;
typedef std::vector<CellState> CellCollection;
