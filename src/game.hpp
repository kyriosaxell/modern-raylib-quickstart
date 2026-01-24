#ifndef SPACEINVADERS_GAME_HPP
#define SPACEINVADERS_GAME_HPP

#include "mysteryship.hpp"
#include "alien.hpp"
#include "obstacle.hpp"
#include "spaceship.hpp"

class Game {
	public:
		Game();
		~Game();
		void Draw() const;
		void Update();
		void HandleInput();

	private:
		void DeleteInactiveLasers();
		std::vector<Obstacle> m_CreateObstacles();
		static std::vector<Alien> s_CreateAliens();
		void m_MoveAliens();
		void m_MoveDownAliens(float distance);
		void m_AlienShootLaser();
		void CheckForCollisions();
		Spaceship m_Spaceship;
		std::vector<Obstacle> m_Obstacles;
		std::vector<Alien> m_Aliens;
		float m_Speed{};
		int m_AliensDirections{};
		std::vector<Laser> m_AlienLasers;
		float m_TimeLastAlienFired{};
		constexpr static float s_AlienLaserShootInterval = 0.35;
		Mysteryship m_MysteryShip;
		float m_MysteryShipSpawnInterval;
		float m_MysteryTimeLastSpawn;
};

#endif
