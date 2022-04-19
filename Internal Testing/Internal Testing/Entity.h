#pragma once
#include <Windows.h>
#include "Offsets.h"
#include "Memory.h"


namespace Ent {
	uintptr_t GetLocalPlayer() {
		return Mem::ReadMemory<uintptr_t>(GameGlobals::clientBase + dwLocalPlayer);
	}

	bool IsEnemy(uintptr_t player) {
		int localPlayerTeamNum = Mem::ReadMemory<int>(GetLocalPlayer() + m_iTeamNum);
		int playerTeamNum = Mem::ReadMemory<int>(player + m_iTeamNum);

		if (playerTeamNum == localPlayerTeamNum) {
			return false;
		}
		else {
			return true;
		}
	}

	bool IsAlive(uintptr_t player) {
		int playerHealth = Mem::ReadMemory<int>(player + m_iHealth);

		if (playerHealth > 0 && playerHealth <= 100) {
			return true;
		}
		else {
			return false;
		}
	}

	bool IsDormant(uintptr_t player) {
		bool isDormant = Mem::ReadMemory<bool>(player + m_bDormant);

		if (isDormant == true) {
			return true;
		}
		else {
			return false;
		}
	}
}