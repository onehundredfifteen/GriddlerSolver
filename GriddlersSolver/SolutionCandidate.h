#pragma once

#include "./Griddlers/Griddler.h"
#include "./Rows/MutableRow.h"
#include "./Approach/ConstraintProvider.h"

class SolutionCandidate
{
public:
	SolutionCandidate(const Griddler &pattern, const ConstraintProvider &approachProvider);
	
	ColumnCollection GetSolvedColumnPattern(int column) const;
	std::vector<ColumnCollection> GetSolvedColumnPattern() const;

	CellCollection GetRowResult(int row) const;

	bool SolutionCandidate::operator==(const SolutionCandidate& other) const;
	
	/*
	void PrintToStream(std::ostream &stream);*/

	bool isSolved(const Griddler& pattern) const;

	friend class Mutation;
	void mutate(const Mutation& mutation);
	void crossingOver(SolutionCandidate& partner, double chance);
	
public:
	const int colCount;
	const int rowCount;

private:
	std::vector<MutableRow> rows;

};