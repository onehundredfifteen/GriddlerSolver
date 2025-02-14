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
	//CellCollection GetColumnResult(int column) const;
	//std::vector<CellCollection> GetResult() const;
	/*
	void DoCrossingOver(GriddlerCandidate * partner, double chance);
	void DoMutate(double chance);

	void PrintToStream(std::ostream &stream);

	//double Fitness;*/

	bool isSolved(const Griddler& pattern) const;

	void mutate(const Mutation& mutation);

	friend class Mutation;
public:
	const int colCount;
	const int rowCount;

private:
	std::vector<MutableRow> rows;

};