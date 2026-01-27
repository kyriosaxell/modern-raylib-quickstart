//
// Created by kyrios on 23/01/26.
//
#ifndef SPACEINVADERS_MYSTERYSHIP_HPP
#define SPACEINVADERS_MYSTERYSHIP_HPP

#include <raylib.h>

class Mysteryship {
	public:
		Mysteryship();
		~Mysteryship();
		void					Update();
		void					Draw() const;
		void					Spawn();
		void					Reset();
		[[nodiscard]] Rectangle GetRect() const;
		bool					is_alive;

	private:
		Vector2	  m_Position{};
		Texture2D m_Image{};
		int		  m_Speed{};
};

#endif // SPACEINVADERS_MYSTERYSHIP_HPP
