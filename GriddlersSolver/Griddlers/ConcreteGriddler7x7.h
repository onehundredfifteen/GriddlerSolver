#pragma once

#include "GriddlerPreset.h"

class ConcreteGriddler7x7 : public GriddlerPreset
{
public:
	std::vector<SpanCollection> GetSolution() const override;

protected:
	std::vector<BlockCollection> initRows() const override;
	std::vector<ColumnCollection> initCols() const override;
};