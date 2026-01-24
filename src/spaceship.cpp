//
// Created by kyrios on 19/01/26.
//

#include "spaceship.hpp"

Spaceship::Spaceship() {
	image = LoadTexture("spaceship.png");
	position.x = static_cast<float>(GetScreenWidth() - image.width) / 2;
	position.y = static_cast<float>(GetScreenHeight() - image.height);
	m_LastFireTime = 0.0;
}

Spaceship::~Spaceship() {
	UnloadTexture(image);
}

void Spaceship::Draw() const {
	DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft() {
	if (position.x <= -1) {
		return;
	}
	position.x += -spaceship_speed;
}

void Spaceship::MoveRight() {
	if (position.x >= static_cast<float>(GetScreenWidth() - image.width)) {
		return;
	}
	position.x += spaceship_speed;
}

void Spaceship::FireLaser() {
	if (GetTime() - m_LastFireTime >= 0.25) {
		lasers.push_back(Laser{{position.x + static_cast<float>(image.width) / 2 - 2, position.y}, -laser_speed});
		m_LastFireTime = GetTime();
	}
}

Rectangle Spaceship::GetRect() const {
	return {position.x, position.y, static_cast<float>(image.width), static_cast<float>(image.height)};
}
