#pragma once
#include <Windows.h>
#include "Memory.h"
#include "Offsets.h"
#include "Entity.h"

void ToggleRadar() {
	for (int i = 0; i < 64; i++) {
		uintptr_t player = Mem::ReadMemory<uintptr_t>(GameGlobals::clientBase + dwEntityList + i * 0x10);

		if (player) {
			if (Ent::IsAlive(player) == true && Ent::IsEnemy(player) == true && Ent::IsDormant(player) == false) {
				Mem::WriteMemory<bool>(player + m_bSpotted, true);
			}
		}
	}
}