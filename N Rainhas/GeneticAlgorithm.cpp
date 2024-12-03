#include "GeneticAlgorithm.h"

//--------------------------------------------------------------------------------------------------

GeneticAlgorithm::GeneticAlgorithm(NQueens* queens, int generations, int population, float mutationRate) :
	LocalSearch(queens)
{
	Population population1(population), population2(population);
	Chromosome parent1, parent2, offspring;

	// Inicializa a população com valores aleatórios
	for (auto& individual : population1)
		for (auto& gene : individual)
			gene = Random::GenerateRow();

	for (int generation{}; generation < generations; generation++)
	{
		if (queens->CheckAttacks() == 0)
			break;

		std::cout << "Geracao: " << generation << "\n\n";

		population2.clear();

		for (int i{}; i < population1.size(); i++)
		{
			SelectChromosome(parent1, population1);
			SelectChromosome(parent2, population1);
			Crossover(offspring, parent1, parent2);
			Mutate(offspring, mutationRate);

			population2.push_back(offspring);

			queens->Move(offspring);
		}

		std::swap(population1, population2);
	}
}

//--------------------------------------------------------------------------------------------------

void GeneticAlgorithm::SelectChromosome(Chromosome& parent, const Population& population)
{
	fitnessGroups.clear();
	weights.clear();

	// Agrupa os indivíduos com base no fitness
	for (int i{}; i < population.size(); i++)
	{
		int fitness{ EvaluateFitness(population[i]) };
		fitnessGroups[fitness].push_back(i);
	}
	
	// Guarda os pesos no vetor
	for (const auto& pair : fitnessGroups)
		weights.push_back(pair.first);

	// Distribuição para simular uma roleta
	std::discrete_distribution dist{ weights.begin(), weights.end() };

	// Escolhe um grupo usando a distribuição discreta
	auto& choosed{ fitnessGroups[weights[dist(Random::mt)]] };

	// Escolhe um indivíduo aleatório do grupo selecionado
	std::uniform_int_distribution<int> rand(0, int(choosed.size() - 1));
	parent = population[choosed[rand(Random::mt)]];
}

//--------------------------------------------------------------------------------------------------

void GeneticAlgorithm::Crossover(Chromosome& offspring, const Chromosome& parent1, const Chromosome& parent2)
{
	int point{ Random::GenerateRow() };

	std::copy(parent1.begin(), parent1.begin() + point, offspring.begin());
	std::copy(parent2.begin() + point, parent2.end(), offspring.begin() + point);
}

//--------------------------------------------------------------------------------------------------

void GeneticAlgorithm::Mutate(Chromosome& offspring, float mutationRate)
{
	if (mutationRate > Random::GenerateReal())
	{
		auto neighbour{ GenerateNeighbour() };
		offspring[neighbour.column] = neighbour.row;
	}
}

//--------------------------------------------------------------------------------------------------
