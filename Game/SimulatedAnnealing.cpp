#include "SimulatedAnnealing.h"

//--------------------------------------------------------------------------------------------------

SimulatedAnnealing::SimulatedAnnealing(Board& board, int iterations) :
	LocalSearch{ board }
{
	// Obtém o número atual de ataques
	int current{ board.CheckAttacks() };

	for (int i{}; i < iterations; i++)
	{	
		// Calcula a temperatura atual com base na iteração
		float temperature{ 1.f - i / iterations };

		// Se a temperatura chegar a 0 ou o problema for resolvido, encerra a busca
		if (temperature == 0 || current == 0)
			return;

		// Gera um estado vizinho aleatório.
		auto neighbour{ GenerateNeighbour() };

		// Calcula a diferença do número de ataques entre o estado atual e o vizinho
		int deltaE{ current - neighbour.attacks };

		// Aceita movimento se melhorar o estado senão com probabilidade e^(deltaE / temperatura)
		if (deltaE > 0 || std::exp(deltaE / temperature) > Random::GenerateReal())
		{
			current = neighbour.attacks;
			board.MoveQueen(neighbour.column, neighbour.row);
		}

		std::cout << "Iteracao " << i << std::endl;
	}
}

//--------------------------------------------------------------------------------------------------
