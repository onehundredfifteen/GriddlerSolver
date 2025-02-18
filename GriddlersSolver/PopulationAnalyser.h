#pragma once

#include <optional>
#include "./types.h"
#include "SolutionCandidate.h"

class PopulationAnalyser
{ 
private:
    const Population& population;
    const Scores& scores;

    double pop_min, pop_max, pop_avg, pop_med;
    Population::const_iterator elite;

public:
	PopulationAnalyser(const Population& _population, const Scores& _scores);

	void refresh();
    std::optional<std::reference_wrapper<const SolutionCandidate>> getSolvedCandidate(const Griddler& pattern) const;
    
    const SolutionCandidate& getElite() const {
        return *elite;
    }
    double getMin() const {
        return pop_min;
    }
    double getMax() const {
        return pop_max;
    }
    double getAvg() const {
        return pop_avg;
    }
    double getMed() const {
        return pop_med;
    }
	//Scores sorted_scores//

private:
	double findMedian();
};

