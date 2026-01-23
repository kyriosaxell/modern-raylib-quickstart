//
// Created by kyrios on 21/01/26.
//

#include "block.hpp"

Block::Block(const Vector2 position) {
	this->position = position;
}

void Block::Draw() const {
	DrawRectangle(position.x, position.y, 3, 3,YELLOW);
}
