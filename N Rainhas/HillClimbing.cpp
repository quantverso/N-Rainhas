#include "HillClimbing.h"
#include "Queen.h"
#include <array>

//--------------------------------------------------------------------------------------------------

HillClimbing::HillClimbing(NQueens* queens) :
	LocalSearch{ queens }
{
	// Obt�m o n�mero atual de ataques
	int current{ queens->CheckAttacks() };

	while (true)
	{
		// Tenta encontrar um estado melhor usando a heur�stica
		auto neighbour{ Heuristic() };

		// Se o n�mero de ataques no melhor vizinho for maior ou igual ao estado atual
		if (neighbour.attacks >= current)
		{
			// Se o estado atual n�o tem conflitos termina a busca
			if (current == 0)
				return;

			// Caso contr�rio, embaralha o tabuleiro
			queens->Shuffle();
			current = queens->CheckAttacks();
			continue;
		}

		// Atualiza para a posi��o do melhor vizinho
		current = neighbour.attacks;
		queens->Move(neighbour.column, neighbour.row);
	}
}


//--------------------------------------------------------------------------------------------------

HillClimbing::Move HillClimbing::Heuristic()
{
	// Armazena o melhor movimento encontrado
	Move best;
	best.attacks = queens->CheckAttacks();
	
	for (int col{}; col < NQueens::N; col++)
	{
		// Armazena a posi��o original
		int originRow{ queens->GetRow(col) };

		for (int row{}; row < NQueens::N; row++)
		{
			if (row == originRow)
				continue;

			// Move a rainha para a posi��o vizinha
			queens->Move(col, row);
			int current{ queens->CheckAttacks() };

			// Se o estado resulta em menos ataques, atualiza o melhor movimento
			if (current < best.attacks)
			{
				best.attacks = current;
				best.column = col;
				best.row = row;
			}
		}

		// Restaura a rainha para sua posi��o original
		queens->Move(col, originRow);
	}

	return best;
}

//--------------------------------------------------------------------------------------------------
