#include "HillClimbing.h"
#include "Queen.h"
#include <array>

//--------------------------------------------------------------------------------------------------

HillClimbing::HillClimbing(Board& board) :
	LocalSearch{ board }
{
	// Obtém o número atual de ataques
	int current{ board.CheckAttacks() };

	while (true)
	{
		// Tenta encontrar um estado melhor usando a heurística
		auto neighbour{ Heuristic() };

		// Se o número de ataques no melhor vizinho for maior ou igual ao estado atual
		if (neighbour.attacks >= current)
		{
			// Se o estado atual não tem conflitos termina a busca
			if (current == 0)
				return;

			// Caso contrário, embaralha o tabuleiro
			board.Shuffle();
			current = board.CheckAttacks();
			continue;
		}

		// Atualiza para a posição do melhor vizinho
		current = neighbour.attacks;
		board.MoveQueen(neighbour.column, neighbour.row);
	}
}


//--------------------------------------------------------------------------------------------------

HillClimbing::Move HillClimbing::Heuristic()
{
	// Armazena o melhor movimento encontrado
	Move best;
	best.attacks = board.CheckAttacks();
	
	for (int col{}; col < Board::NumberOfQueens; col++)
	{
		// Armazena a posição original
		int originRow{ board.GetQueen(col).row };

		for (int row{}; row < Board::NumberOfQueens; row++)
		{
			if (row == originRow)
				continue;

			// Move a rainha para a posição vizinha
			board.MoveQueen(col, row);
			int current{ board.CheckAttacks() };

			// Se o estado resulta em menos ataques, atualiza o melhor movimento
			if (current < best.attacks)
			{
				best.attacks = current;
				best.column = col;
				best.row = row;
			}
		}

		// Restaura a rainha para sua posição original
		board.MoveQueen(col, originRow);
	}

	return best;
}

//--------------------------------------------------------------------------------------------------
