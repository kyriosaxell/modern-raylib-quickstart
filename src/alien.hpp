#pragma once
#include <raylib.h>


class Alien {
	public:
		Alien(int type, Vector2 position);
		void Draw() const;
		void Update(int direction);
		[[nodiscard]] int GetType() const;
		static void UnloadImages();
		static Texture2D s_AlienImages[3];
		int type;
		Vector2 position{};
};
