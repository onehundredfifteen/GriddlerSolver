#pragma once

#include "./Griddlers/Griddler.h"
#include "./Rows/MutableRow.h"
#include "./Approach/ConstraintProvider.h"

class SolutionCandidate
{
public:
	SolutionCandidate(const Griddler &pattern, const ConstraintProvider &approachProvider);
	//SolutionCandidate(const SolutionCandidate& other);

	//SolutionCandidate& operator=(const SolutionCandidate& other);
	
	ColumnCollection getSolvedColumnPattern(int column) const;
	std::vector<ColumnCollection> getSolvedColumnPattern() const;
	CellCollection GetRowResult(int row) const;

	bool SolutionCandidate::operator==(const SolutionCandidate& other) const;
	void printToStream(std::ostream &stream) const;

	bool isSolved(const Griddler& pattern) const;
	bool isLethal() const;

	friend class Mutation;
	void mutate(const Mutation& mutation);
	void crossingOver(SolutionCandidate& partner, double chance);
	
public:
	const int colCount;
	const int rowCount;

private:
	std::vector<MutableRow> rows;

};