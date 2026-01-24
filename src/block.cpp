//
// Created by kyrios on 21/01/26.
//

#include "block.hpp"

Block::Block(const Vector2 position) {
	this->m_Position = position;
}

void Block::Draw() const {
	DrawRectangle(m_Position.x, m_Position.y, 3, 3,YELLOW);
}

Rectangle Block::GetRect() const {
	return {m_Position.x, m_Position.y, 3, 3};
}
