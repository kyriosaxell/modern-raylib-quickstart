//
// Created by kyrios on 23/01/26.
//

#include "mysteryship.hpp"

Mysteryship::Mysteryship() {
	m_Image	 = LoadTexture("mystery.png");
	is_alive = false;
}

Mysteryship::~Mysteryship() {
	UnloadTexture(m_Image);
}

void Mysteryship::Draw() const {
	if (is_alive) {
		DrawTextureV(m_Image, m_Position, WHITE);
	}
}

void Mysteryship::Update() {
	if (is_alive) {
		m_Position.x += static_cast<float>(m_Speed);
		if (m_Position.x > static_cast<float>(GetScreenWidth() - m_Image.width - 30) || m_Position.x < 30) {
			is_alive = false;
		}
	}
}

void Mysteryship::Spawn() {
	m_Position.y = 30;
	if (const int side = GetRandomValue(0, 1); side == 0) {
		m_Position.x = 25;
		m_Speed		 = 3;
	} else {
		m_Position.x = static_cast<float>(GetScreenWidth() - m_Image.width) - 30;
		m_Speed		 = -3;
	}
	is_alive = true;
}

void Mysteryship::Reset() {
	is_alive = false;
}

Rectangle Mysteryship::GetRect() const {
	if (is_alive) {
		return {m_Position.x, m_Position.y, static_cast<float>(m_Image.width), static_cast<float>(m_Image.height)};
	}
	return {m_Position.x, m_Position.y, 0, 0};
}
