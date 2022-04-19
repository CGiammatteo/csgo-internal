#pragma once
#include <Windows.h>
#include "Memory.h"
#include "Offsets.h"
#include "Entity.h"
#include <cstdint>

struct Color {
	std::uint8_t r{}, g{}, b{};
};

constexpr const auto chosenColor = Color{0, 0, 255};

void ToggleChams() {
	for (int i = 0; i < 64; i++) {
		uintptr_t player = Mem::ReadMemory<uintptr_t>(GameGlobals::clientBase + dwEntityList + i * 0x10);

		if (player) {
			if (Ent::IsAlive(player) == true && Ent::IsEnemy(player) == true && Ent::IsDormant(player) == false) {
				Mem::WriteMemory<Color>(player + m_clrRender, chosenColor);

				float brightness = 25.f;
				const auto _this = static_cast<std::uintptr_t>(GameGlobals::engineBase + model_ambient_min - 0x2c);
				Mem::WriteMemory<std::int32_t>(GameGlobals::engineBase + model_ambient_min, *reinterpret_cast<std::uintptr_t*>(&brightness) ^ _this);
			}
		}
	}
}