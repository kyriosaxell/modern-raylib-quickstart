#include "game.hpp"
#include "raylib.h"

#include "resource_dir.h"
#include "telemetry.hpp"

constexpr Color grey   = {29, 29, 27, 255};
constexpr Color yellow = {243, 216, 63, 255};

int main() {
	constexpr int offset		= 50;
	constexpr int window_width	= 1280;
	constexpr int window_height = 800;

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SetTargetFPS(120);

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so
	// we can load from it


	// Create the window and OpenGL context
	InitWindow(window_width + offset, window_height + (2 * offset), "Hello Raylib");

	SearchAndSetResourceDir("resources");

	const Font		font			 = LoadFontEx("font/monogram.ttf", 64, 0, 0);
	const Texture2D space_ship_image = LoadTexture("spaceship.png");
	Game game;

	// Game loop
	while (!WindowShouldClose()) {
		game.HandleInput();
		game.Update();

		BeginDrawing();
		ClearBackground(grey);

		DrawRectangleRoundedLinesEx({15, 15, window_width + 20, window_height + 70}, 0.18f, 20, 2, yellow);
		DrawLineEx({15, window_height}, {window_width + 35, window_height}, 3, yellow);

		if (game.run) {
			DrawTextEx(font, "LEVEL 01", {window_width - 170, 830}, 34, 2, yellow);
		} else {
			DrawTextEx(font, "GAME OVER", {window_width - 220, 830}, 34, 2, yellow);
		}

		float x = 50.0;
		for (int i = 0; i < game.GetLives(); ++i) {
			DrawTextureV(space_ship_image, {x, 830}, WHITE);
			x += 50;
		}

		game.Draw();
		Telemetry::DrawPerformanceOverlay();
		EndDrawing();
	}

	UnloadTexture(space_ship_image);

	CloseWindow();
	return 0;
}
