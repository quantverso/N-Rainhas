#include "LocalSearch.h"

//--------------------------------------------------------------------------------------------------

LocalSearch::LocalSearch(NQueens* queens) :
    queens{ queens }
{
    system("cls");
}

//--------------------------------------------------------------------------------------------------

LocalSearch::Move LocalSearch::GenerateNeighbour()
{
    int column{ Random::GenerateRow() };

    // Armazena a posi��o original
    int originRow{ queens->GetRow(column) };

    // Gera uma posi��o diferente da original
    int row;
    do {
        row = Random::GenerateRow();
    } while (row == originRow);

    // Move a rainha para a posi��o vizinha e calcula a quantidade de ataques
    queens->Move(column, row);
    int attacks{ queens->CheckAttacks() };

    // Restaura a rainha para sua posi��o original
    queens->Move(column, originRow);

    return {
        column,
        row,
        attacks
    };
}

//--------------------------------------------------------------------------------------------------
