#pragma once

#include "WindowSystem/WindowSystem.h"

class WindowSystem;
class RHI;

class Engine {
public:
	Engine();
	~Engine();
	void InitEngine();
	void DestroyEngine();
	WindowSystem* GetWindowSystem();
private:
	WindowSystem* m_window_system;
	RHI* m_rhi;
};

extern Engine* GEngine;


