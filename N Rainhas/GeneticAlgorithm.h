#ifndef QUANTVERSO_GENETICALGORITHM_H
#define QUANTVERSO_GENETICALGORITHM_H

//--------------------------------------------------------------------------------------------------

#include "LocalSearch.h"
#include "Random.h"
#include <array>
#include <vector>
#include <unordered_map>

using Chromosome = std::array<int, NQueens::N>;
using Population = std::vector<Chromosome>;
using FitnessGroups = std::unordered_map<int, std::vector<int>>;

//--------------------------------------------------------------------------------------------------

class GeneticAlgorithm : public LocalSearch
{
public:
	GeneticAlgorithm(NQueens* queens, int generations, int population, float mutationRate);

private:
	void SelectChromosome(Chromosome& parent, const Population& population);
	void Crossover(Chromosome& offspring, const Chromosome& parent1, const Chromosome& parent2);
	void Mutate(Chromosome& offspring, float mutationRate);
	int EvaluateFitness(const Chromosome& chromosome);

	FitnessGroups	 fitnessGroups;
	std::vector<int> weights;
};

//--------------------------------------------------------------------------------------------------

inline int GeneticAlgorithm::EvaluateFitness(const Chromosome& chromosome)
{
	return (NQueens::N - 1) * NQueens::N / 2 - queens->CheckAttacks(chromosome) + 1;
}

//--------------------------------------------------------------------------------------------------

#endif
