#pragma once
#include <Windows.h>

#define dwLocalPlayer 0xDB65DC
#define dwEntityList 0x4DD245C
#define m_iHealth 0x100
#define m_iTeamNum 0xF4
#define m_bDormant 0xED
#define m_bSpotted 0x93D
#define m_iDefaultFOV 0x333C
#define m_clrRender 0x70
#define model_ambient_min 0x59003C

#define dwGlowObjectManager 0x531B048
#define m_iGlowIndex 0x10488

namespace GameGlobals {
	DWORD clientBase;
	DWORD engineBase;
}