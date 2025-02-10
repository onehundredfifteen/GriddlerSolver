#pragma once

#include "SolutionCandidate.h"
#include "Griddlers/Griddler.h"

class PopulationGenerator {
public:
    static std::vector<SolutionCandidate> Generate(const int N, const Griddler& pattern, const ConstraintProvider& approachProvider) {
        std::vector<SolutionCandidate> population;
        population.reserve(N);
        
        for (int i = 0; i < N; ++i)
            population.emplace_back(pattern, approachProvider);

        return std::move(population);
    }
};

/*// Factory class
class ProductFactory {
public:
    enum ProductType {
        TYPE_A,
        TYPE_B
    };

    static std::unique_ptr<Product> createProduct(ProductType type) {
        switch (type) {
            case TYPE_A:
                return std::make_unique<ProductA>();
            case TYPE_B:
                return std::make_unique<ProductB>();
            default:
                return nullptr;
        }
    }*/
