#pragma once

#include <raylib.h>

class Block {
	public:
		explicit Block(Vector2 position);
		void	  Draw() const;
		Rectangle GetRect() const;

	private:
		Vector2 m_Position{};
};
