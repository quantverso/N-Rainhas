#include "NQueens.h"
#include "HillClimbing.h"
#include "SimulatedAnnealing.h"
#include "GeneticAlgorithm.h"
#include "Random.h"
#include <algorithm>

//--------------------------------------------------------------------------------------------------

NQueens::NQueens() :
	square{ Rectangle::Solid },
	queens{},
	rows{}
{
}

//--------------------------------------------------------------------------------------------------

void NQueens::Start()
{
	float squareSize{ window.Size().width / N };

	square.Size(squareSize, squareSize);

	for (int i{}; i < N; i++)
	{
		queens[i] = CreateObject<Queen>(std::to_string(i).c_str(), i, rows[i]);
		queens[i]->transform.Size(squareSize, squareSize);
	}

	Shuffle();
}

//--------------------------------------------------------------------------------------------------

void NQueens::Update()
{
	// Subida de encosta
	if (Keyboard::KeyDown(Keyboard::Num1))
		HillClimbing{ this };

	// Têmpera simulada
	if (Keyboard::KeyDown(Keyboard::Num2))
		SimulatedAnnealing{ this, 20000 };

	// Algorítimo genético
	if (Keyboard::KeyDown(Keyboard::Num3))
		GeneticAlgorithm{ this, 500, 200, 0.38f };

	// Embaralha as rainhas
	if (Keyboard::KeyPressed(Keyboard::Num0))
		Shuffle();

	Scene::Update();
}

//--------------------------------------------------------------------------------------------------

void NQueens::Draw()
{
	CheckAttacks();

	for (int i{}; i < N; i++)
	{
		for (int j{}; j < N; j++)
		{
			// Posiciona as casas
			square.Position(i * square.Size().width, j * square.Size().width);

			// Desenha o tabuleiro
			(i + j) % 2 ? square.Color(Color(130, 130, 130)) : square.Color(Color(200, 200, 200));
			window.Draw(&square);

			// Desenha casas de rainhas sob ataque
			if (rows[i] == j && queens[i]->GetAttackStatus())
			{
				square.Color(Color(230, 0, 50, 120));
				window.Draw(&square);
			}
		}
	}

	Scene::Draw();
}

//--------------------------------------------------------------------------------------------------

void NQueens::Shuffle()
{
	std::generate(rows.begin(), rows.end(), Random::GenerateRow);
}

//--------------------------------------------------------------------------------------------------

int NQueens::CheckAttacks(const std::array<int, N>& rows) const
{
	int attacks{};

	for (int i{}; i < N - 1; i++)
	{
		for (int j{ i + 1 }; j < N; j++)
		{
			if (rows[i] == rows[j] || abs(rows[i] - rows[j]) == abs(i - j))
			{	
				attacks++;

				if (&this->rows == &rows)
				{
					queens[i]->SetAttackStatus(Queen::UnderAttack);
					queens[j]->SetAttackStatus(Queen::UnderAttack);
				}
			}
		}
	}

	return attacks;
}

//--------------------------------------------------------------------------------------------------

int NQueens::CheckAttacks() const
{
	for (auto& queen : queens)
		queen->SetAttackStatus(Queen::Safe);

	return CheckAttacks(rows);
}

//--------------------------------------------------------------------------------------------------
