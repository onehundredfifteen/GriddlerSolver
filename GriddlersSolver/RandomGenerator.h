#pragma once

#include <random>

//as singleton
class RandomGenerator
{
private:
	std::mt19937 generator;

	RandomGenerator() : generator(std::random_device()()) {}
	RandomGenerator(const RandomGenerator &) {}
public:
    static RandomGenerator & Next() {
        static RandomGenerator rg;
        return rg;
    }

	int operator()(int low, int high) { 
		if(low >= high) {
			high = 0;
		}
        std::uniform_int_distribution<int> distribution(low, high);
        return distribution(generator);
    }

	double operator()(double low, double high) { 
		if(low >= high)
		{
			high = 0;
		}
        std::uniform_real_distribution<double> distribution(low, high);
        return distribution(generator);
    }
};