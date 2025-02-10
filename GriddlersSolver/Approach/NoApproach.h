#pragma once
#include "ConstraintProvider.h"

class NoApproach : public ConstraintProvider
{
public:
	NoApproach() : ConstraintProvider()
	{}

public: 
	const ConstrainedRow& getRow(int row) const override {
		return constrained_row_but_empty;
	}

private: 
	static ConstrainedRow constrained_row_but_empty;
};