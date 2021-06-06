#include "Engine/Engine.h"
#include "RHI/RHI.h"


Engine* GEngine = nullptr;

Engine::Engine()
{

}

Engine::~Engine()
{
	{
		DestroyEngine();
	}
}

void Engine::InitEngine()
{
	m_window_system = new WindowSystem();
	RHI::CreateRHIInstance();
	m_rhi = GRHI;
	m_rhi->InitRHI();
}

void Engine::DestroyEngine()
{
	delete m_window_system;
}

WindowSystem* Engine::GetWindowSystem()
{
	if (GEngine == nullptr)
	{
		LOG(LogType::LOG_ERROR, "1");
	}
	 return m_window_system; 
}
