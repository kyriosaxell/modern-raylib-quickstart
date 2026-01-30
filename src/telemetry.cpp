//
// Created by kyrios on 22/01/26.
//

#include "telemetry.hpp"

#include <raylib.h>

void Telemetry::DrawPerformanceOverlay() {
	const int fps = GetFPS();
	const float frameTime = GetFrameTime() * 1000.0f; // Convertir a milisegundos (latencia)

	// Raylib no da CPU/GPU/RAM directamente por ser multiplataforma simple
	// Pero podemos mostrar los FPS y el FrameTime que son los más importantes
	DrawText(TextFormat("FPS: %i", fps), 10, 10, 20, GREEN);
	DrawText(TextFormat("Latencia: %.2f ms", frameTime), 10, 30, 20, MAROON);
}
