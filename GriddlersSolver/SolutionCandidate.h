#pragma once

#include "./Griddlers/Griddler.h"
#include "./Rows/MutableRow.h"
#include "./Approach/ConstraintProvider.h"

class SolutionCandidate
{
public:
	const int colCount;
	const int rowCount;

private:
	std::vector<MutableRow> rows;
	const Griddler& pattern;

public:
	SolutionCandidate(const Griddler &_pattern, const ConstraintProvider &_approachProvider);
	//SolutionCandidate(const SolutionCandidate& other);

	//SolutionCandidate& operator=(const SolutionCandidate& other);
	
	ColumnCollection getSolvedColumnPattern(int column) const;
	std::vector<ColumnCollection> getSolvedColumnPattern() const;
	CellCollection getRowAsCells(int row) const;
	const Griddler& getPattern() const;

	bool SolutionCandidate::operator==(const SolutionCandidate& other) const;
	void printToStream(std::ostream &stream) const;

	bool isSolved() const;
	bool isLethal() const;

	friend class Mutation;
	void mutate(const Mutation& mutation);
	void crossingOver(SolutionCandidate& partner, double chance);
};