#include "../stdafx.h"
#include "./Mutation.h"
#include "../SolutionCandidate.h"

Mutation::Mutation(double _mutation_rate)
	: mutation_rate(std::clamp(_mutation_rate, 0.0, 1.0))
{}

std::vector<MutableRow>& Mutation::getMutableRows(SolutionCandidate& candidate) const {
	return candidate.rows;
}
