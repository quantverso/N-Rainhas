#include "Queen.h"

//--------------------------------------------------------------------------------------------------

Queen::Queen(int column, int& row) :
	column(column),
	row(row),
	offset({}),
	collision(false),
	attackStatus(false)
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
			Mouse::Position().x - transform.Position().x,
			Mouse::Position().y - transform.Position().y
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
			row = int(transform.Position().y / transform.Size().height + 0.5);
	}
}

//--------------------------------------------------------------------------------------------------
