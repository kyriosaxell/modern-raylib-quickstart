#pragma once
#include <raylib.h>

class Laser {
	public:
		Laser(Vector2 position, float speed);
		void Update();
		void Draw() const;
		bool active;

	private:
		Vector2 m_Position{};
		float m_Speed;
};
