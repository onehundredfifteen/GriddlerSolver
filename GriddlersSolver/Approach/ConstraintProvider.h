#pragma once

#include "../Griddlers/Griddler.h"
#include "../Rows/ConstrainedRow.h"
#include "../SolutionTable.h"

class ConstraintProvider
{
public:
	ConstraintProvider(int imageHeight, int imageWidth)
		: content(imageHeight, imageWidth),
		height(imageHeight),
		width(imageWidth)
	{}
	ConstraintProvider(const Griddler &pattern)
		: ConstraintProvider(pattern.GetImageHeight(), pattern.GetImageWidth())
	{}

protected:
	ConstraintProvider() 
		: ConstraintProvider(0, 0)
	{}

public: 
	virtual const ConstrainedRow& getRow(int row) const = 0;

protected:
	const int height;
	const int width;
	SolutionTable content;
};