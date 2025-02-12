#pragma once

#include "GriddlerPreset.h"

class DiagonalGriddler5x5 : public GriddlerPreset
{
public:
	DiagonalGriddler5x5() {
		solution = this->initSolution();
		pattern_rows = this->initRows();
		pattern_cols = this->initCols();
	}
	
	constexpr bool hasSolution() const {
		return true;
	}

protected:
	std::vector<SpanCollection> initSolution() const override {
		return { {0}, {1}, {2}, {3}, {4} };
	}

	std::vector<BlockCollection> initRows() const override {
		return { {1}, {1}, {1}, {1}, {1} };
	}

	std::vector<ColumnCollection> initCols() const override {
		return { {1}, {1}, {1}, {1}, {1} };
	}
};