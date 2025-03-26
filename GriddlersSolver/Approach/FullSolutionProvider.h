#pragma once
#include "ConstraintProvider.h"
#include "../Griddlers/GriddlerPreset.h"

class FullSolutionProvider : public ConstraintProvider
{
public:
	FullSolutionProvider(const GriddlerPreset& preset)
		: ConstraintProvider(preset)
	{
		solved_rows.reserve(preset.GetImageWidth() * preset.GetImageHeight());
		auto solution_row = preset.solution.begin();

		for (auto row : preset.getRowPattern()) {
			// Move cells into content
			GriddlerRow solved(row, *(solution_row++), preset.GetImageWidth());
			solved_rows.emplace_back(solved);
		}
	}

	const ConstrainedRow& getRow(int row) const override {
		return solved_rows.at(row);
	}

protected:
	std::vector<ConstrainedRow> solved_rows;
};