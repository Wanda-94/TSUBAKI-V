// TSUBAKI-V.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "GlobalSetting/GlobalSetting.h"


#include <memory>
#include "Engine/Engine.h"
#include "RHI/RHI.h"


void MainLoop()
{
	while (!GEngine->GetWindowSystem()->WindowShouldClose())
	{
		//std::cout << "run" << std::endl;
	}
}

int main()
{
	GEngine = new Engine();
	GEngine->InitEngine();
	MainLoop();
	return 0;

}

// TODO: 在此处引用程序需要的其他标头。
