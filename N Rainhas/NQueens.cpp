#include "NQueens.h"
#include "Queen.h"
#include "HillClimbing.h"
#include "SimulatedAnnealing.h"
#include "GeneticAlgorithm.h"
#include "Random.h"

//--------------------------------------------------------------------------------------------------

Board NQueens::board{};

//--------------------------------------------------------------------------------------------------

NQueens::NQueens() :
	square{ Rectangle::Solid }
{
}

//--------------------------------------------------------------------------------------------------

void NQueens::Start()
{
	float squareSize{ window.Size().width / board.NumberOfQueens };

	square.Size(squareSize, squareSize);

	for (int i{}; i < board.NumberOfQueens; ++i)
	{
		Queen* queen{ CreateObject<Queen>() };
		queen->transform.Size(squareSize, squareSize);
	}

	board.Shuffle();
}

//--------------------------------------------------------------------------------------------------

void NQueens::Update()
{
	// Subida de encosta
	if (Keyboard::KeyDown(Keyboard::Num1))
		HillClimbing{ board };

	// Têmpera simulada
	if (Keyboard::KeyDown(Keyboard::Num2))
		SimulatedAnnealing{ board, 20000 };

	// Algorítimo genético
	if (Keyboard::KeyDown(Keyboard::Num3))
		GeneticAlgorithm{ board, 500, 200, 0.38f };

	// Embaralha as rainhas
	if (Keyboard::KeyPressed(Keyboard::Num0))
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
			square.Position(i * square.Size().width, j * square.Size().width);

			// Desenha o tabuleiro
			(i + j) % 2 ? square.Color(Color(130, 130, 130)) : square.Color(Color(200, 200, 200));
			window.Draw(&square);

			// Desenha casas de rainhas sob ataque
			auto& queen{ board.GetQueen(i) };
			if (queen.row == j && queen.status)
			{
				square.Color(Color(230, 0, 50, 120));
				window.Draw(&square);
			}
		}
	}

	Scene::Draw();
}

//--------------------------------------------------------------------------------------------------
