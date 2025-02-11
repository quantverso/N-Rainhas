#include "LocalSearch.h"

//--------------------------------------------------------------------------------------------------

LocalSearch::LocalSearch(Board& board) :
    board{ board }
{
    system("cls");
}

//--------------------------------------------------------------------------------------------------

LocalSearch::Move LocalSearch::GenerateNeighbour()
{
    int column{ Random::GenerateRow() };

    // Armazena a posi��o original
    int originRow{ board.GetQueen(column).row };

    // Gera uma posi��o diferente da original
    int row;
    do {
        row = Random::GenerateRow();
    } while (row == originRow);

    // Move a rainha para a posi��o vizinha e calcula a quantidade de ataques
    board.MoveQueen(column, row);
    int attacks{ board.CheckAttacks() };

    // Restaura a rainha para sua posi��o original
    board.MoveQueen(column, originRow);

    return {
        column,
        row,
        attacks
    };
}

//--------------------------------------------------------------------------------------------------
