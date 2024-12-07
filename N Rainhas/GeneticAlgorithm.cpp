#include "GeneticAlgorithm.h"

//--------------------------------------------------------------------------------------------------

GeneticAlgorithm::GeneticAlgorithm(NQueens* queens, int generations, int population, float mutationRate)
    : LocalSearch{ queens }
{
    Population population1(population), population2(population);
    Chromosome parent1, parent2;

    // Inicializa a população inicial com valores aleatórios
    for (auto& individual : population1)
        std::generate(individual.begin(), individual.end(), Random::GenerateRow);

    // Processa as gerações até encontrar uma solução ou atingir o limite
    for (int generation{}; generation < generations; generation++)
    {
        std::cout << "Geracao: " << generation << std::endl;

        for (auto& offspring : population2)
        {
            // Seleciona os pais
            SelectChromosome(parent1, population1);
            SelectChromosome(parent2, population1);

            // Realiza o cruzamento
            int point{ Random::GenerateRow() };
            std::copy(parent1.begin(), parent1.begin() + point, offspring.begin());
            std::copy(parent2.begin() + point, parent2.end(), offspring.begin() + point);

            // Aplica mutação
            if (Random::GenerateReal() < mutationRate)
            {
                auto neighbour{ GenerateNeighbour() };
                offspring[neighbour.column] = neighbour.row;
            }

            // Verifica se a solução foi encontrada
            if (queens->CheckAttacks(offspring) == 0)
            {
                queens->Move(offspring);
                return;
            }
        }

        // Troca as populações
        std::swap(population1, population2);
    }
}



//--------------------------------------------------------------------------------------------------

void GeneticAlgorithm::SelectChromosome(Chromosome& parent, const Population& population)
{
	fitnessGroups.clear();
	rouletteWeights.clear();

	// Agrupa os indivíduos com base no fitness
	for (const auto& individual : population)
	{
		int fitness{ EvaluateFitness(individual) };
		fitnessGroups[fitness].push_back(&individual);
	}
	
	// Guarda os pesos no vetor
	for (const auto& pair : fitnessGroups)
		rouletteWeights.push_back(pair.first);

	// Distribuição para simular uma roleta
	std::discrete_distribution roulette{ rouletteWeights.begin(), rouletteWeights.end() };

	// Escolhe um grupo usando a distribuição discreta
	auto& choosed{ fitnessGroups[rouletteWeights[roulette(Random::mt)]] };

	// Escolhe um indivíduo aleatório do grupo selecionado
	std::uniform_int_distribution<int> randomIndividual{ 0, int(choosed.size() - 1) };
	parent = *choosed[randomIndividual(Random::mt)];
}

//--------------------------------------------------------------------------------------------------
