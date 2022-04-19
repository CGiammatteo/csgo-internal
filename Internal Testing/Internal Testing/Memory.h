#pragma once
#include <Windows.h>

namespace Mem {
	template<typename T> T ReadMemory(uintptr_t address) {
		try { 
			return *(T*)address;
		}
		catch (...) { 
			return T(); 
		}
	}

	template<typename T> void WriteMemory(uintptr_t address, T value) {
		try { 
			*(T*)address = value; 
		}
		catch (...) { 
			return; 
		}
	}
}