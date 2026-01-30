#pragma once
#include <raylib.h>


class Alien {
	public:
		Alien(int type, Vector2 position);
		void					Draw() const;
		void					Update(int direction);
		static void				s_UnloadImages();
		static Texture2D		s_AlienImages[3];
		[[nodiscard]] Rectangle GetRect() const;
		int						type;
		Vector2					position{};
};
