#pragma once

#include <algorithm>

#include "./ConstrainedRow.h"
#include "./GriddlerRow.h"
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
	//MutableRow(const MutableRow& other);
	const bool final;

public:
	bool isValid() const;
	void sanitize();
	SpanCollection& getSpans();

	void crossingOver(MutableRow& partner);
	void mutate(const Mutation& effect);

private:
	void randomizeRow();
	void randomizeRowConstraintWise(const ConstrainedRow& constraintProvider);
	
	void trimSpansToWidth();
	void fixMiddleZeroes();
	void fixImpossibleBigSpans();
	void ensureOneMaxSpanAtTime();

	bool _initFinal() const;
};