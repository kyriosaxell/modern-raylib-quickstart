//
// Created by kyrios on 19/01/26.
//

#include "spaceship.hpp"
#include <raylib.h>

Spaceship::Spaceship() {
	m_Image		   = LoadTexture("spaceship.png");
	m_Position.x   = static_cast<float>(GetScreenWidth() - m_Image.width) / 2;
	m_Position.y   = static_cast<float>(GetScreenHeight() - m_Image.height) - 110;
	m_LastFireTime = 0.0;
	m_LaserSound = LoadSound("sound/laser.ogg");
}

Spaceship::~Spaceship() {
	UnloadTexture(m_Image);
	UnloadSound(m_LaserSound);
}

void Spaceship::Draw() const {
	DrawTextureV(m_Image, m_Position, WHITE);
}

void Spaceship::MoveLeft() {
	m_Position.x += -s_SpaceShipSpeed;
	if (m_Position.x < 40) {
		m_Position.x = 40;
	}
}

void Spaceship::MoveRight() {
	m_Position.x += s_SpaceShipSpeed;
	if (m_Position.x > static_cast<float>(GetScreenWidth() - m_Image.width)) {
		m_Position.x = static_cast<float>(GetScreenWidth() - m_Image.width) - 20;
	}
}

void Spaceship::FireLaser() {
	if (GetTime() - m_LastFireTime >= s_LastFireTimeInterval) {
		lasers.push_back(
			Laser{{m_Position.x + static_cast<float>(m_Image.width) / 2 - 2, m_Position.y}, -s_LaserSpeed}
		);
		PlaySound(m_LaserSound);
		m_LastFireTime = GetTime();
	}
}

Rectangle Spaceship::GetRect() const {
	return {m_Position.x, m_Position.y, static_cast<float>(m_Image.width), static_cast<float>(m_Image.height)};
}

void Spaceship::Reset() {
	m_Position.x = static_cast<float>(GetScreenWidth() - m_Image.width) / 2.0f;
	m_Position.y = static_cast<float>(GetScreenHeight() - m_Image.height) - 100;
	lasers.clear();
}
