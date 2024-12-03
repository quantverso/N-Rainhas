#include "LocalSearch.h"

//--------------------------------------------------------------------------------------------------

LocalSearch::LocalSearch(NQueens* queens) :
    queens(queens)
{
    system("cls");
}

//--------------------------------------------------------------------------------------------------

LocalSearch::Move LocalSearch::GenerateNeighbour()
{
    int column{ Random::GenerateRow() };

    // Armazena a posição original
    int originRow{ queens->GetRow(column) };

    // Gera uma posição diferente da original
    int row{ Random::GenerateRow() };
    while (row == originRow)
        row = Random::GenerateRow();

    // Move a rainha para a posição vizinha e calcula a quantidade de ataques
    queens->Move(column, row);
    int attacks{ queens->CheckAttacks() };

    // Restaura a rainha para sua posição original
    queens->Move(column, originRow);

    return {
        column,
        row,
        attacks
    };
}

//--------------------------------------------------------------------------------------------------
