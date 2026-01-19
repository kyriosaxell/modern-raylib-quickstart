#include "raylib.h"

#include "resource_dir.h"

int main() {
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SetTargetFPS(60);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	const Texture wabbit = LoadTexture("wabbit_alpha.png");

	// Game loop
	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("Hello Raylib", 200, 200, 20,WHITE);

		DrawTexture(wabbit, 400, 200, WHITE);

		EndDrawing();
	}

	// A must!
	UnloadTexture(wabbit);

	CloseWindow();
	return 0;
}
