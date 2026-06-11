#pragma once

#include "Estimator.h"
#include <vector>
#include <stdexcept>

/*template <typename Candidate = SolutionCandidate, typename... Args>
static Population Generate(int N, Args&&... args)
{
    Population population;
    population.reserve(N);

    for (int i = 0; i < N; ++i)
        population.emplace_back(std::forward<Args>(args)...);

    return population;
}*/
//typedef std::pair<const Estimator*, double> WeightedEstimator;

class ChainedEstimator : public Estimator
{
public:
    using Estimator::candidateFitness;

    struct WeightedEstimator {
        const Estimator* estimator;
        double weight;
    };

    ChainedEstimator(const Griddler& _pattern, std::vector<WeightedEstimator> estimators)
        : Estimator(_pattern), chain(std::move(estimators))
    {
        if (chain.empty()) {
            throw std::invalid_argument("ChainedEstimator requires at least one estimator.");
        }
    }

    double candidateFitness(const std::vector<ColumnCollection>& candidate) const override
    {
        double total_weight = 0.0;
        double weighted_score = 0.0;

        for (const auto& entry : chain) {
            if (entry.estimator == nullptr) {
                continue;
            }
            weighted_score += entry.estimator->candidateFitness(candidate) * entry.weight;
            total_weight += entry.weight;
        }

        return total_weight != 0.0 ? weighted_score / total_weight : weighted_score;
    }


private:
    std::vector<WeightedEstimator> chain;
};
