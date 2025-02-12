#pragma once

#include <map>
#include "FullSolutionProvider.h"

//for test estimators purpose
class WarpedSolution : public FullSolutionProvider
{
public:
	WarpedSolution(const GriddlerPreset& preset)
		: FullSolutionProvider(preset)
	{	
	}

	void warpRow(int row, const ConstrainedRow &new_row) {
		warped_rows.emplace(row, new_row);
	}

	const ConstrainedRow& getRow(int row) const override {
		auto it = warped_rows.find(row);
		if (it != warped_rows.end())
			return it->second;
		else return FullSolutionProvider::getRow(row);
	}

protected:
	std::map<int, ConstrainedRow> warped_rows;
};

