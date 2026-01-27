//
// Created by kyrios on 20/01/26.
//

#include "game.hpp"

Game::Game() {
	InitGame();
}

Game::~Game() {
	Alien::s_UnloadImages();
}

void Game::Update() {
	if (run) {
		if (const double currentTime = GetTime(); currentTime - m_MysteryTimeLastSpawn > m_MysteryShipSpawnInterval) {
			m_MysteryShip.Spawn();
			m_MysteryTimeLastSpawn	   = static_cast<float>(GetTime());
			m_MysteryShipSpawnInterval = static_cast<float>(GetRandomValue(10, 20));
		}

		for (auto& laser : m_Spaceship.lasers) {
			laser.Update();
		}
		m_MoveAliens();

		m_AlienShootLaser();

		for (auto& laser : m_AlienLasers) {
			laser.Update();
		}

		DeleteInactiveLasers();
		m_MysteryShip.Update();

		CheckForCollisions();
		return;
	}

	if (IsKeyDown(KEY_ENTER)) {
		Reset();
		InitGame();
	}
}

void Game::Draw() const {
	// Draw the spaceship
	m_Spaceship.Draw();

	// Draw the lasers shoots
	for (auto& laser : m_Spaceship.lasers) {
		laser.Draw();
	}

	// Draw the obstacles
	for (auto& obstacle : m_Obstacles) {
		obstacle.Draw();
	}

	// Draw the aliens
	for (auto& alien : m_Aliens) {
		alien.Draw();
	}

	for (auto& laser : m_AlienLasers) {
		laser.Draw();
	}
	m_MysteryShip.Draw();
}

void Game::HandleInput() {
	if (run) {
		if (IsKeyDown(KEY_RIGHT)) m_Spaceship.MoveRight();
		if (IsKeyDown(KEY_LEFT)) m_Spaceship.MoveLeft();
		if (IsKeyPressed(KEY_SPACE)) m_Spaceship.FireLaser();
	}
}

void Game::DeleteInactiveLasers() {
	for (auto it = m_Spaceship.lasers.begin(); it != m_Spaceship.lasers.end();) {
		if (!it->active) {
			it = m_Spaceship.lasers.erase(it);
		} else {
			++it;
		}
	}

	for (auto it = m_AlienLasers.begin(); it != m_AlienLasers.end();) {
		if (!it->active) {
			it = m_AlienLasers.erase(it);
		} else {
			++it;
		}
	}
}

std::vector<Obstacle> Game::m_CreateObstacles() {
	const float obstacleWidth = static_cast<float>(Obstacle::grid[0].size()) * 3;
	const float gap			  = (static_cast<float>(GetScreenWidth()) - (4 * obstacleWidth)) / 5;
	for (int i = 0; i < 4; ++i) {
		const float offsetX = static_cast<float>((i + 1)) * gap + i * obstacleWidth;
		m_Obstacles.push_back(Obstacle{{offsetX, static_cast<float>(GetScreenHeight() - 200)}});
	}
	return m_Obstacles;
}

std::vector<Alien> Game::s_CreateAliens() {
	std::vector<Alien> aliens;
	for (int row = 0; row < 5; ++row) {
		for (int column = 0; column < 11; ++column) {
			int alienType;
			if (row == 0) {
				alienType = 3;
			} else if (row == 1 || row == 2) {
				alienType = 2;
			} else {
				alienType = 1;
			}
			float const x = 350 + static_cast<float>(column) * 55;
			float const y = 80 + static_cast<float>(row) * 55;
			aliens.push_back(Alien{alienType, {x, y}});
		}
	}
	return aliens;
}

void Game::m_MoveAliens() {
	for (auto& alien : m_Aliens) {
		if (const auto image_width = static_cast<float>(Alien::s_AlienImages[alien.type - 1].width);
			alien.position.x + image_width > static_cast<float>(GetScreenWidth()) - 50) {
			m_AliensDirections = -1;
			m_MoveDownAliens(3);
		}
		if (alien.position.x < 25) {
			m_AliensDirections = 1;
			m_MoveDownAliens(3);
		}
		alien.Update(m_AliensDirections);
	}
}

void Game::m_MoveDownAliens(const float distance) {
	for (auto& alien : m_Aliens) {
		alien.position.y += distance;
	}
}

void Game::m_AlienShootLaser() {
	if (const double currentTime = GetTime();
		currentTime - m_TimeLastAlienFired > s_AlienLaserShootInterval && !m_Aliens.empty()) {
		const int	 randomIndex = GetRandomValue(0, static_cast<int>(m_Aliens.size()) - 1);
		const Alien& alien		 = m_Aliens[randomIndex];
		const auto&	 img		 = Alien::s_AlienImages[alien.type - 1];
		m_AlienLasers.push_back(
			Laser{
				{alien.position.x + static_cast<float>(img.width) / 2.0f,
				 alien.position.y + static_cast<float>(img.height)},
				6
			}
		);
		m_TimeLastAlienFired = static_cast<float>(GetTime());
	}
}

void Game::CheckForCollisions() {
	/// Checks collisions from Spaceship laser
	for (auto& laser : m_Spaceship.lasers) {
		// Checks for collisions with aliens
		auto it = m_Aliens.begin();
		while (it != m_Aliens.end()) {
			if (CheckCollisionRecs(it->GetRect(), laser.GetRect())) {
				it			 = m_Aliens.erase(it);
				laser.active = false;
			} else {
				++it; // Moves to the next alien
			}
		}

		// Checks for collisions with obstacles
		for (auto& obstacle : m_Obstacles) {
			auto node = obstacle.blocks.begin();
			while (node != obstacle.blocks.end()) {
				if (CheckCollisionRecs(node->GetRect(), laser.GetRect())) {
					node		 = obstacle.blocks.erase(node);
					laser.active = false;
				} else {
					++node;
				}
			}
		}

		if (CheckCollisionRecs(m_MysteryShip.GetRect(), laser.GetRect())) {
			m_MysteryShip.is_alive = false;
			laser.active		   = false;
		}
	}

	/// Checks for all collisions from Aliens
	for (auto& alien_laser : m_AlienLasers) {

		// Checks for collisions with obstacles
		for (auto& obstacle : m_Obstacles) {
			auto node = obstacle.blocks.begin();
			while (node != obstacle.blocks.end()) {
				if (CheckCollisionRecs(node->GetRect(), alien_laser.GetRect())) {
					node			   = obstacle.blocks.erase(node);
					alien_laser.active = false;
				} else {
					++node;
				}
			}
		}

		// Check for collisions to Spaceship
		if (CheckCollisionRecs(alien_laser.GetRect(), m_Spaceship.GetRect())) {
			alien_laser.active = false;
			if (m_SpaceShipLives > 1) {
				--m_SpaceShipLives;
			} else {
				m_GameOver();
			}
		}
	}

	for (auto& alien : m_Aliens) {
		for (auto& obstacle : m_Obstacles) {
			auto node = obstacle.blocks.begin();
			while (node != obstacle.blocks.end()) {
				if (CheckCollisionRecs(node->GetRect(), alien.GetRect())) {
					node = obstacle.blocks.erase(node);
				} else {
					++node;
				}
			}
		}
	}
}

void Game::m_GameOver() {
	run = false;
}

void Game::Reset() {
	m_Spaceship.Reset();
	m_MysteryShip.Reset();
	m_Aliens.clear();
	m_AlienLasers.clear();
	m_Obstacles.clear();
}

void Game::InitGame() {
	m_Obstacles				   = m_CreateObstacles();
	m_Aliens				   = s_CreateAliens();
	m_AliensDirections		   = 1;
	m_TimeLastAlienFired	   = 0.0;
	m_MysteryShipSpawnInterval = static_cast<float>(GetRandomValue(10, 20));
	m_SpaceShipLives		   = 3;
	run						   = true;
}
