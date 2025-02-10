#pragma once

#include "GriddlerPreset.h"

class ConcreteGriddler7x7 : public GriddlerPreset
{
public:
	ConcreteGriddler7x7();
	
public:
	std::vector<SpanCollection> initSolution() const override;

protected:
	std::vector<BlockCollection> initRows() const override;
	std::vector<ColumnCollection> initCols() const override;
};