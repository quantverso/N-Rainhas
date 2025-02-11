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
	sprite.SetTexture(&queen);
}

//--------------------------------------------------------------------------------------------------

void Queen::Update()
{
	// Verifica se o mouse foi clicado sobre a rainha
	if (Mouse::IsButtonPressed(Mouse::Left) && window.IsEventTriggered(Window::MouseButtonDown))
	{
		Point point{ Mouse::GetPosition() };
		collision = transform.CheckCollision(&point);

		offset = {
			point.Position().x - transform.Position().x,
			point.Position().y - transform.Position().y
		};
	}

	// Move a rainha com o mouse
	if (collision)
		transform.Position(Mouse::GetPosition().x - offset.x, Mouse::GetPosition().y - offset.y);

	// Calcula a linha com base na posição da rainha ao liberar o mouse
	if (window.IsEventTriggered(Window::MouseButtonUp))
	{
		collision = false;
		if (transform.Position().y >= 0 && transform.Position().y < window.GetSize().height)
		{
			Board& board{ GetScene<NQueens>()->board};
			board.MoveQueen(column, int(transform.Position().y / transform.GetSize().height + 0.5));
		}
	}
}

//--------------------------------------------------------------------------------------------------

void Queen::Align()
{
	if (!Mouse::IsButtonPressed(Mouse::Left))
	{
		Board& board{ GetScene<NQueens>()->board};
		float x{ transform.GetSize().width * column };
		float y{ transform.GetSize().height * board.GetQueen(column).row };
		transform.Position(x, y);
	}
}

//--------------------------------------------------------------------------------------------------
