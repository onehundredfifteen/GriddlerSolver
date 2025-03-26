#include "./PopulationAnalyser.h"
#include "./Estimators/Estimator.h"

PopulationAnalyser::PopulationAnalyser(const Population& _population, const Scores& _scores)
	: population(_population), scores(_scores), elite(population.cbegin()) {
	
	pop_min = Estimator::LOW_FITNESS;
	pop_max = Estimator::HIGH_FITNESS;
	pop_avg = pop_med = 0.0;

	refresh();
}

void PopulationAnalyser::refresh() {
	double sum = 0.0;

	for (auto it = scores.begin(); it < scores.end(); ++it) {
		if (*it > pop_max) {
			pop_max = *it;
			elite = population.cbegin() + std::distance(scores.begin(), it);
		}
			
		if (*it < pop_min)
			pop_min = *it;

		sum += *it;
	}

	pop_avg = sum / scores.size();
 	pop_med = findMedian();
}

std::optional<std::reference_wrapper<const SolutionCandidate>> PopulationAnalyser::getSolvedCandidate() const {
	auto solved = std::find_if(population.begin(), population.end(), 
		[](const auto& ind) {
			return ind.isSolved();
		});
	
	if (solved != population.end()) {
		bool g = solved->isSolved();

		return std::cref(*solved);
	}
		
	
	return std::nullopt;
}

double PopulationAnalyser::findMedian() {
	Scores sorted = scores;
	std::sort(sorted.begin(), sorted.end());
	size_t size = sorted.size();

	if (size == 0) {
		throw std::domain_error("Median is undefined for an empty data set.");
	}

	if (size % 2 == 0) {
		// Even number of elements: average the two middle elements
		return (sorted[size / 2 - 1] + sorted[size / 2]) / 2.0;
	}
	else {
		// Odd number of elements: middle element
		return sorted[size / 2];
	}
}
