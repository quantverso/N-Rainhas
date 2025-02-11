#include "GeneticAlgorithm.h"

//--------------------------------------------------------------------------------------------------

GeneticAlgorithm::GeneticAlgorithm(Board& board, int generations, int population, float mutationRate) :
    LocalSearch{ board }
{
    Population population1(population), population2(population);
    Chromosome parent1, parent2;

    // Inicializa a popula��o com valores aleat�rios
    for (auto& individual : population1)
    {
        individual.Shuffle();
    }

    // Processa as gera��es at� encontrar uma solu��o ou atingir o limite
    for (int gen{}; gen < generations; gen++)
    {
        std::cout << "Geracao: " << gen << std::endl;

        for (auto& offspring : population2)
        {
            // Seleciona os pais
            SelectChromosome(parent1, population1);
            SelectChromosome(parent2, population1);

            // Realiza o cruzamento
            int point{ Random::GenerateRow() };
            offspring.Copy(parent1, 0, point);
            offspring.Copy(parent2, point);

            // Aplica muta��o
            if (Random::GenerateReal() < mutationRate)
            {
                auto neighbour{ GenerateNeighbour() };
                offspring.MoveQueen(neighbour.column, neighbour.row);
            }

            // Verifica se a solu��o foi encontrada
            if (offspring.CheckAttacks() == 0)
            {
                board.Copy(offspring);
                return;
            }
        }

        // Troca as popula��es
        std::swap(population1, population2);
    }
}

//--------------------------------------------------------------------------------------------------

void GeneticAlgorithm::SelectChromosome(Chromosome& parent, const Population& population)
{
	fitnessGroups.clear();
	rouletteWeights.clear();

	// Agrupa os indiv�duos com base no fitness
	for (auto& individual : population)
	{
		int fitness{ EvaluateFitness(individual) };
		fitnessGroups[fitness].push_back(&individual);
	}
	
	// Guarda os pesos no vetor
	for (const auto& pair : fitnessGroups)
		rouletteWeights.push_back(pair.first);

	// Distribui��o para simular uma roleta
	std::discrete_distribution roulette{ rouletteWeights.begin(), rouletteWeights.end() };

	// Escolhe um grupo usando a distribui��o discreta
	auto& choosed{ fitnessGroups[rouletteWeights[roulette(Random::mt)]] };

	// Escolhe um indiv�duo aleat�rio do grupo selecionado
	std::uniform_int_distribution<int> randomIndividual{ 0, int(choosed.size() - 1) };
	parent = *choosed[randomIndividual(Random::mt)];
}

//--------------------------------------------------------------------------------------------------
