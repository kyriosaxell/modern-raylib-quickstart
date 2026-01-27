//
// Created by kyrios on 20/01/26.
//

#include "laser.hpp"

Laser::Laser(const Vector2 position, const float speed) {
	this->m_Position = position;
	this->m_Speed	 = speed;
	active			 = true;
}

void Laser::Update() {
	m_Position.y += m_Speed;
	if (active) {
		if (m_Position.y >= static_cast<float>(GetScreenHeight()-100) || m_Position.y < 25) {
			active = false;
		}
	}
}

void Laser::Draw() const {
	DrawRectangle(static_cast<int>(m_Position.x), static_cast<int>(m_Position.y), 4, 15, {243, 216, 63, 255});
}

Rectangle Laser::GetRect() const {
	return {m_Position.x, m_Position.y, 4, 15};
}
