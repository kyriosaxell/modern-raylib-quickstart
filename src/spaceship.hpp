#ifndef SPACEINVADERS_SPACESHIP_HPP
#define SPACEINVADERS_SPACESHIP_HPP

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
		Rectangle GetRect() const;
		std::vector<Laser> lasers;

	private:
		Texture2D image{};
		Vector2 position{};
		static constexpr float spaceship_speed = 5.0f;
		static constexpr float laser_speed = 7.f;
		double m_LastFireTime;
};

#endif
