#pragma once

#include "GriddlerPreset.h"

class ConcreteGriddler7x7 : public GriddlerPreset
{
public:
	ConcreteGriddler7x7() {
		solution = this->initSolution();
		pattern_rows = this->initRows();
		pattern_cols = this->initCols();
	}
	
	constexpr bool hasSolution() const {
		return true;
	}

protected:
	std::vector<SpanCollection> initSolution() const override {
		return { {1}, {0, 2}, {5}, {3, 1}, {2, 1}, {1, 4}, {0, 1} };
	}

	std::vector<BlockCollection> initRows() const override {
		return { {4}, {2, 2}, {1}, {1, 1}, {1, 1}, {1, 1}, {1, 5} };
	}

	std::vector<ColumnCollection> initCols() const override {
		return { {1, 1}, {2, 1}, {1, 1, 1}, {1, 1, 1}, {2, 1, 1}, {3, 1}, {2} };
	}
};