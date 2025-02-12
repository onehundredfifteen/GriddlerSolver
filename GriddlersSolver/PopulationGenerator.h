#pragma once

#include "SolutionCandidate.h"
#include "Griddlers/Griddler.h"

class PopulationGenerator {
public:
    static Population Generate(const int N, const Griddler& pattern, const ConstraintProvider& approachProvider) {
        Population population;
        population.reserve(N);
        
        for (int i = 0; i < N; ++i)
            population.emplace_back(pattern, approachProvider);

        return std::move(population);
    }

    /*template<typename... Args>
    static Population createPopulationFromArgs(Args&&... args) {
        Population population;
        population.reserve(sizeof...(args)); // assuming each object takes 1 argument
        (population.emplace_back(std::forward<Args>(args)...), ...);
        return population;
    }*/

    template <typename T = SolutionCandidate, typename... Args>
    static Population createPopulationFromArgs(Args const&... args)
    {
        return { args... };
    }

    /*template <typename T = SolutionCandidate>
    static Population createPopulationFromArgs(std::initializer_list<T> elements)
    {
        return std::vector<T>(elements.begin(), elements.end());
    }*/
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
