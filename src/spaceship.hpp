#pragma once
#include <raylib.h>
#include <vector>

#include "laser.hpp"

class Spaceship {
	public:
		Spaceship();
		~Spaceship();
		void Draw() const;
		void MoveLeft();
		void MoveRight();
		void FireLaser();
		std::vector<Laser> lasers;

	private:
		Texture2D image{};
		Vector2 position{};
		static constexpr float spaceship_speed = 5.0f;
		static constexpr float laser_speed = 7.f;
		double lastFireTime;
};
