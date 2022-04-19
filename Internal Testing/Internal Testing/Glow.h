#pragma once

#include <Windows.h>
#include "Memory.h"
#include "Offsets.h"
#include "Entity.h"

struct GlowStruct {
	int m_nNextFreeSlot;
	void* m_pEntity;
	float m_flRed;
	float m_flGreen;
	float m_flBlue;
	float m_flAlpha;
	bool m_bGlowAlphaCappedByRenderAlpha;
	float m_flGlowAlphaFunctionOfMaxVelocity;
	float m_flGlowAlphaMax;
	float m_flGlowPulseOverdrive;
	bool m_bRenderWhenOccluded;
	bool m_bRenderWhenUnoccluded;
	bool m_bFullBloomRender;
	int m_nFullBloomStencilTestValue;
	int m_nGlowStyle;
	int m_nSplitScreenSlot;
} Glow;

void ToggleGlow() {
	for (int i = 0; i < 64; i++) {
		uintptr_t player = Mem::ReadMemory<uintptr_t>(GameGlobals::clientBase + dwEntityList + i * 0x10);

		if (player) {
			if (Ent::IsAlive(player) == true && Ent::IsEnemy(player) == true && Ent::IsDormant(player) == false) {

				uintptr_t objManager = Mem::ReadMemory<uintptr_t>(GameGlobals::clientBase + dwGlowObjectManager);
				int idx = Mem::ReadMemory<int>(player + m_iGlowIndex);

				GlowStruct glowStr = Mem::ReadMemory<GlowStruct>(objManager + (idx * 0x38));

				glowStr.m_flRed = 1.0f;
				glowStr.m_flGreen = 1.0f;
				glowStr.m_flBlue = 0.0f;
				glowStr.m_flAlpha = 1.0f;
				glowStr.m_bRenderWhenOccluded = true;
				glowStr.m_nGlowStyle = 0; // 0 = through walls glow, 1 = chams type of glow, 2 = 0 outline with 1 chams

				Mem::WriteMemory<GlowStruct>(objManager + (idx * 0x38), glowStr);
			}
		}
	}
}