//
// Created by kyrios on 21/01/26.
//

#include "alien.hpp"
#include <iostream>

Texture2D Alien::s_AlienImages[3] = {};

Alien::Alien(const int type, const Vector2 position) {
	this->type	   = type;
	this->position = position;

	switch (type) {
		case 1:
			s_AlienImages[0] = LoadTexture("alien_1.png");
			break;
		case 2:
			s_AlienImages[1] = LoadTexture("alien_2.png");
			break;
		case 3:
			s_AlienImages[2] = LoadTexture("alien_3.png");
			break;
		default:
			s_AlienImages[0] = LoadTexture("alien_1.png");
			break;
	}
}

void Alien::Draw() const {
	DrawTextureV(s_AlienImages[type - 1], position, WHITE);
}

void Alien::Update(const int direction) {
	position.x += static_cast<float>(direction);
}

void Alien::s_UnloadImages() {
	for (int i = 0; i < 3; i++) {
		std::cout << "Unloading imagen! " << i << std::endl;
		UnloadTexture(s_AlienImages[i]);
	}
}

Rectangle Alien::GetRect() const {
	return {
		position.x, position.y, static_cast<float>(s_AlienImages[type - 1].width),
		static_cast<float>(s_AlienImages[type - 1].height)
	};
}
