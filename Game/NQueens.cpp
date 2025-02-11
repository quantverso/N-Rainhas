#include "NQueens.h"
#include "Queen.h"
#include "HillClimbing.h"
#include "SimulatedAnnealing.h"
#include "GeneticAlgorithm.h"
#include "Random.h"

//--------------------------------------------------------------------------------------------------

NQueens::NQueens() :
	square{ Rectangle::Solid },
	board{}
{
}

//--------------------------------------------------------------------------------------------------

void NQueens::Start()
{
	float squareSize{ window.GetSize().width / board.NumberOfQueens };

	square.SetSize(squareSize, squareSize);

	for (int i{}; i < board.NumberOfQueens; ++i)
	{
		Queen* queen{ CreateObject<Queen>() };
		queen->transform.SetSize(squareSize, squareSize);
	}

	board.Shuffle();
}

//--------------------------------------------------------------------------------------------------

void NQueens::Update()
{
	// Subida de encosta
	if (Keyboard::IsKeyDown(Keyboard::Num1))
		HillClimbing{ board };

	// Têmpera simulada
	if (Keyboard::IsKeyDown(Keyboard::Num2))
		SimulatedAnnealing{ board, 20000 };

	// Algorítimo genético
	if (Keyboard::IsKeyDown(Keyboard::Num3))
		GeneticAlgorithm{ board, 500, 200, 0.38f };

	// Embaralha as rainhas
	if (Keyboard::IsKeyPressed(Keyboard::Num0))
		board.Shuffle();

	Scene::Update();
}

//--------------------------------------------------------------------------------------------------

void NQueens::Draw()
{
	board.CheckAttacks();

	for (int i{}; i < board.NumberOfQueens; i++)
	{
		for (int j{}; j < board.NumberOfQueens; j++)
		{
			// Posiciona as casas
			square.Position(i * square.GetSize().width, j * square.GetSize().width);

			// Desenha o tabuleiro
			(i + j) % 2 ? square.SetColor(Color(130, 130, 130)) : square.SetColor(Color(200, 200, 200));
			window.Draw(&square);

			// Desenha casas de rainhas sob ataque
			auto& queen{ board.GetQueen(i) };
			if (queen.row == j && queen.status)
			{
				square.SetColor(Color(230, 0, 50, 120));
				window.Draw(&square);
			}
		}
	}

	Scene::Draw();
}

//--------------------------------------------------------------------------------------------------
