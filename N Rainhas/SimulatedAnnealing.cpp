#include "SimulatedAnnealing.h"

//--------------------------------------------------------------------------------------------------

SimulatedAnnealing::SimulatedAnnealing(NQueens* queens, int iterations) :
	LocalSearch{ queens }
{
	// Obt�m o n�mero atual de ataques
	int current{ queens->CheckAttacks() };

	for (int i{}; i < iterations; i++)
	{	
		// Calcula a temperatura atual com base na itera��o
		float temperature{ 1.f - i / iterations };

		// Se a temperatura chegar a 0 ou o problema for resolvido, encerra a busca
		if (temperature == 0 || current == 0)
			return;

		// Gera um estado vizinho aleat�rio.
		auto neighbour{ GenerateNeighbour() };

		// Calcula a diferen�a do n�mero de ataques entre o estado atual e o vizinho
		int deltaE{ current - neighbour.attacks };

		// Aceita movimento se melhorar o estado sen�o com probabilidade e^(deltaE / temperatura)
		if (deltaE > 0 || std::exp(deltaE / temperature) > Random::GenerateReal())
		{
			current = neighbour.attacks;
			queens->Move(neighbour.column, neighbour.row);
		}

		std::cout << "Iteracao " << i << std::endl;
	}
}

//--------------------------------------------------------------------------------------------------
