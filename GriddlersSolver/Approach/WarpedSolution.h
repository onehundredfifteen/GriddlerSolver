#pragma once

#include <map>
#include "FullSolutionProvider.h"

//for testing estimators purpose
class WarpedSolution : public FullSolutionProvider
{
public:
	WarpedSolution(const GriddlerPreset& preset)
		: FullSolutionProvider(preset)
	{	
	}

	void warpRow(int index, const ConstrainedRow &new_row) {
		warped_rows.emplace(index, new_row);
	}

	const ConstrainedRow& getRow(int index) const override {
		auto it = warped_rows.find(index);
		if (it != warped_rows.end())
			return it->second;
		else return FullSolutionProvider::getRow(index);
	}

protected:
	std::map<int, ConstrainedRow> warped_rows;
};

