#pragma once

#include "Griddler.h"

class GriddlerPreset : public Griddler
{
public:
	constexpr bool hasSolution() const {
		return false;
	}
	std::vector<SpanCollection> solution;

protected:
	virtual std::vector<SpanCollection> initSolution() const {
		return {};
	};
	virtual std::vector<BlockCollection> initRows() const {
		return {};
	};
	virtual std::vector<ColumnCollection> initCols() const {
		return {};
	};
};