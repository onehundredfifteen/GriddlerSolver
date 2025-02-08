#pragma once

#include "Griddler.h"

class GriddlerPreset : public Griddler
{
public:
	GriddlerPreset()
		: Griddler(initRows(), initCols()) 
	{}

public:
	virtual std::vector<SpanCollection> getSolution() const = 0;
	constexpr bool hasSolution() const {
		return false;
	}

protected:
	virtual std::vector<BlockCollection> initRows() const = 0;
	virtual std::vector<ColumnCollection> initCols() const = 0;
};