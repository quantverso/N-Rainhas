#include "Queen.h"
#include "NQueens.h"

//--------------------------------------------------------------------------------------------------

Queen::Queen() :
	column{ []()
		{
			static int column;
			return column++;
		}()
	},
	offset{},
	collision{}
{
	static Texture queen{ "Resources/queen.png" };
	material.Add(&queen);
}

//--------------------------------------------------------------------------------------------------

void Queen::Update()
{
	// Verifica se o mouse foi clicado sobre a rainha
	if (Mouse::ButtonPressed(Mouse::Left) && window.CheckEvent(Window::MouseButtonDown))
	{
		Point point{ Mouse::Position() };
		collision = transform.CheckCollision(&point);

		offset = {
			point.Position().x - transform.Position().x,
			point.Position().y - transform.Position().y
		};
	}

	// Move a rainha com o mouse
	if (collision)
		transform.Position(Mouse::Position().x - offset.x, Mouse::Position().y - offset.y);

	// Calcula a linha com base na posição da rainha ao liberar o mouse
	if (window.CheckEvent(Window::MouseButtonUp))
	{
		collision = false;
		if (transform.Position().y >= 0 && transform.Position().y < window.Size().height)
			NQueens::board.MoveQueen(column, int(transform.Position().y / transform.Size().height + 0.5));
	}
}

//--------------------------------------------------------------------------------------------------

void Queen::Align()
{
	if (!Mouse::ButtonPressed(Mouse::Left))
		transform.Position(
			transform.Size().width * column, transform.Size().height * NQueens::board.GetQueen(column).row);
}

//--------------------------------------------------------------------------------------------------
