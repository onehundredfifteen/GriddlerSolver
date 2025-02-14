#pragma once

/*
Mutation

visitor pattern

*/

#include <vector>

class MutableRow;
class SolutionCandidate;
typedef std::vector<std::reference_wrapper<MutableRow>> Chromosomes;

class Mutation
{
public:
	Mutation(double _mutation_rate);

	virtual void visit(MutableRow& row) const = 0;
	virtual Chromosomes getAffectedChromosomes(SolutionCandidate& candidate) const = 0;

protected:
	std::vector<MutableRow>& getMutableRows(SolutionCandidate& candidate) const;

protected:
	double mutation_rate;
};