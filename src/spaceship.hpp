#ifndef SPACEINVADERS_SPACESHIP_HPP
#define SPACEINVADERS_SPACESHIP_HPP

#include <raylib.h>
#include <vector>

#include "laser.hpp"

class Spaceship {
	public:
		Spaceship();
		~Spaceship();
		void					Draw() const;
		void					MoveLeft();
		void					MoveRight();
		void					FireLaser();
		[[nodiscard]] Rectangle GetRect() const;
		void					Reset();
		std::vector<Laser>		lasers;

	private:
		Texture2D			   m_Image{};
		Vector2				   m_Position{};
		double				   m_LastFireTime{};
		static constexpr float s_SpaceShipSpeed		  = 5.0f;
		static constexpr float s_LaserSpeed			  = 7.0f;
		static constexpr float s_LastFireTimeInterval = 0.25f;
};

#endif
