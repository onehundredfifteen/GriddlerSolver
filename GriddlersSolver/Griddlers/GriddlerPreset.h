#pragma once

#include "Griddler.h"

class GriddlerPreset : public Griddler
{
public:
	GriddlerPreset()
		: Griddler(initRows(), initCols()) {
	}

public:
	virtual std::vector<SpanCollection> GetSolution() const = 0;

protected:
	virtual std::vector<BlockCollection> initRows() const = 0;
	virtual std::vector<ColumnCollection> initCols() const = 0;
};