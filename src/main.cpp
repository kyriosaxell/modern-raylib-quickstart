#include "game.hpp"
#include "raylib.h"

#include "resource_dir.h"
#include "telemetry.hpp"

int main() {
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SetTargetFPS(120);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	Game game;


	// Game loop
	while (!WindowShouldClose()) {
		game.HandleInput();
		game.Update();

		BeginDrawing();
		ClearBackground(BLACK);

		game.Draw();
		Telemetry::DrawPerformanceOverlay();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
