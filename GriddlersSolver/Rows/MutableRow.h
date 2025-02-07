#pragma once

#include <algorithm>

#include "ConstrainedRow.h"
#include "GriddlerRow.h"
#include "../RandomGenerator.h"
#include "../Mutations/Mutation.h"


/*
MutableRow

MutableRow can mutate

*/

class MutableRow : public GriddlerRow
{
public:
	MutableRow(const BlockCollection& _blocks, int imgwidth, const ConstrainedRow& constraintProvider);

private:
	const bool final;

public:

	bool isValid() const;
	void sanitize();

private:
	void randomizeRow();
	void randomizeRowConstraintWise(const ConstrainedRow& constraintProvider);

	bool _initFinal() const;

	void trimSpansToWidth();

	void fixMiddleZeroes();

	void adjustLastSpan();

	
public:
	SpanCollection& getSpans();

	void CrossingOver(MutableRow& partner);

	void Mutate(Mutation& effect);



	
};