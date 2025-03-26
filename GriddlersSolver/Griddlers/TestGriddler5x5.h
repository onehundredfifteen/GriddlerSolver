#pragma once

#include "GriddlerPreset.h"

/*
		#//#/
		/#//#
		//#/#
		#//#/
		##//#
*/

class TestGriddler5x5 : public GriddlerPreset
{
public:
	TestGriddler5x5() {
		solution = this->initSolution();
		pattern_rows = this->initRows();
		pattern_cols = this->initCols();
	}
	
	constexpr bool hasSolution() const {
		return true;
	}

protected:
	std::vector<SpanCollection> initSolution() const override {
		return { {0, 2}, {1, 2}, {2, 1}, {0, 2}, {0, 2} };
	}

	std::vector<BlockCollection> initRows() const override {
		return { {1, 1}, {1, 1}, {1, 1}, {1, 1}, {2, 1} };
	}

	std::vector<ColumnCollection> initCols() const override {
		return { {1, 2}, {1, 1}, {1}, {1, 1}, {2, 1} };
	}
};